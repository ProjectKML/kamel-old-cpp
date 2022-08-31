//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Game.cpp
//------------------------------------------------------------

#include "Game.hpp"

#include "../Common/Util/STL/pmr_new.hpp"
#include "../Common/Util/Thread/ThreadExtensions.hpp"
#include "../Common/Core/Memory/DefaultMemoryResource.hpp"
#ifdef KML_PLATFORM_WINDOWS
#include "../Platform/Windows/WindowsHelper.hpp"
#endif
#include "../Common/Core/Logging/CustomFlagFormatters.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include "../Common/Util/Config/ConfigParser.hpp"
#include "../Common/Util/Time/DateTime.hpp"
#include "../Common/Core/Event/EventBus.hpp"
#include "../Common/Core/Package/PackageManager.hpp"
#include "../Common/Core/Runtime/RuntimeHost.hpp"
#include "Core/Window/Window.hpp"
#include "../Common/CoreConstants.hpp"
#include "Core/Window/MessageBox.hpp"
#include "Renderer/Renderer.hpp"

namespace KMLEngine {
    template<> Game* Singleton<Game>::_INSTANCE = nullptr;

    void Game::CreateLoggerAndConfigs(zpl_opts& options) noexcept {
#ifdef KML_PLATFORM_WINDOWS
        WindowsHelper::EnableUTF8Support();
#endif

        try {
            auto formatter = std::make_unique<spdlog::pattern_formatter>();
            formatter->add_flag<LogLevelFlagFormatter>('l').add_flag<LogThreadNameFormatter>('t')
                .set_pattern("[%D %H:%M:%S] [%n/%t] [%^%l%$] %v");

            auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            consoleSink->set_formatter(formatter->clone());

            spdlog::set_default_logger(std::make_shared<spdlog::logger>("KMLEngine", spdlog::sinks_init_list({consoleSink})));

            m_engineConfig = ConfigParser::DeserializeFromFile<ConfigEngine>();
            m_clientConfig = ConfigParser::DeserializeFromFile<ConfigClient>();

            if(zpl_opts_has_arg(&options, "log-to-file") != 0 || m_engineConfig.Logger.ShouldLogToFile) {
                auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fmt::format("Logs/KMLEngine_{}.log", DateTime::Now().ToString("%Y-%m-%d_%I-%M-%S")), true);
                fileSink->set_formatter(std::move(formatter));

                spdlog::default_logger()->sinks().push_back(fileSink);
            }
        } catch(const spdlog::spdlog_ex& exception) {
            zpl_printf("[KMLEngine] Initializing logger failed: %s\n", exception.what());
            std::exit(1);
        }
    }

    void Game::CreateWindow(zpl_opts& options) {
        const auto width = static_cast<u32>(zpl_opts_integer(&options, "width", m_clientConfig.Window.Width));
        const auto height = static_cast<u32>(zpl_opts_integer(&options, "height", m_clientConfig.Window.Height));
        const auto fullscreen = zpl_opts_has_arg(&options, "fullscreen") != 0 || m_clientConfig.Window.Fullscreen;

        m_window = new Window(width, height, fullscreen, KML_ENGINE_GAME_NAME);
    }

    void Game::CreateRenderer(zpl_opts& options) {
        m_renderer = new Renderer(1); //TODO:
    }

    void Game::CreateTimer(zpl_opts& options) {
        const auto frameLimit = static_cast<u32>(zpl_opts_integer(&options, "frame-limit", m_clientConfig.Timer.FrameLimit));

        m_timer.Create();
        m_timer.SetIntervalSpan(TimeSpan::FromFrameLimit(frameLimit));
        m_updateInterval = TimeSpan::FromFrameLimit(CoreConstants::TicksPerSecond);
        m_updateIntervalStep = TimeSpan();
    }

    void Game::OnStart(zpl_opts& options) {
        m_eventBus = new EventBus;
        m_packageManager = new PackageManager;
        m_runtimeHost = new RuntimeHost;

        CreateWindow(options);
        CreateRenderer(options);
        CreateTimer(options);
    }

    void Game::OnUpdate(const TimerEventArgs& timerEventArgs) {
        m_window->ProcessEvents(*m_eventBus);
        m_renderer->RenderRuntime(timerEventArgs); //TODO:
    }

    void Game::OnStop() {
        m_timer.Dispose();

        delete m_renderer;
        m_renderer = nullptr;

        delete m_window;
        m_window = nullptr;

        delete m_runtimeHost;
        m_runtimeHost = nullptr;
		
        delete m_packageManager;
        m_packageManager = nullptr;
		
        delete m_eventBus;
        m_eventBus = nullptr;
    }

    void Game::HandleException(const std::exception& exception) const {
        spdlog::critical("Unhandled exception: {}", exception.what());
        MessageBox::Show(MessageBox::Type::Error, "Unhandled exception", exception.what(), m_window);
        std::exit(1);
    }

    Game::Game(zpl_opts& options) {
        m_defaultMemoryResource = kml_stl::pmr_new<DefaultMemoryResource>(std::pmr::new_delete_resource());
        std::pmr::set_default_resource(m_defaultMemoryResource);

        ThreadExtensions::SetCurrentThreadName("MAIN");
        CreateLoggerAndConfigs(options);

        try {
            OnStart(options);
			
            while(!m_window->IsCloseRequested()) {	
                m_timer.Tick([this](const TimerEventArgs& timerEventArgs) { OnUpdate(timerEventArgs); });
            }

            OnStop();
        } catch(const std::exception& exception) {
            HandleException(exception);
        }

        AttachSingleton();
    }

    Game::~Game() {
        DetachSingleton();
		
        ConfigParser::SerializeToFile(m_clientConfig);
        ConfigParser::SerializeToFile(m_engineConfig);

        kml_stl::pmr_delete(std::pmr::new_delete_resource(), m_defaultMemoryResource);
    }
}

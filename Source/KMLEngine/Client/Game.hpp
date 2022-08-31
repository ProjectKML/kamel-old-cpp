//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Game.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_GAME_HPP
#define KMLENGINE_CLIENT_GAME_HPP

#pragma once

#include "../Platform/Types.hpp"
#include "../Common/Util/Traits/Singleton.hpp"
#include "../Common/Util/Traits/Uncopyable.hpp"
#include "../Common/Util/Library/Zpl.hpp"
#include "../Common/Util/Config/ConfigEngine.hpp"
#include "Util/Config/ConfigClient.hpp"
#include "../Common/Util/Time/Timer.hpp"

namespace KMLEngine {
    class DefaultMemoryResource;
    class EventBus;
    class PackageManager;
    class RuntimeHost;
    class Window;
    class Renderer;

    struct TimerEventArgs;
    
    class Game final : public Uncopyable, public Singleton<Game> {
    private:
        DefaultMemoryResource* m_defaultMemoryResource = nullptr;

        ConfigEngine m_engineConfig = {};
        ConfigClient m_clientConfig = {};

        EventBus* m_eventBus = nullptr;
        PackageManager* m_packageManager = nullptr;
        RuntimeHost* m_runtimeHost = nullptr;
        Window* m_window = nullptr;
        Renderer* m_renderer = nullptr;

        Timer m_timer;
        TimeSpan m_updateInterval, m_updateIntervalStep;

        void CreateLoggerAndConfigs(zpl_opts& options) noexcept;
        void CreateWindow(zpl_opts& options);
        void CreateRenderer(zpl_opts& options);
        void CreateTimer(zpl_opts& options);

        void OnStart(zpl_opts& options);
        void OnUpdate(const TimerEventArgs& timerEventArgs);
        void OnStop();
        
        void HandleException(const std::exception& exception) const;
    public:
        explicit Game(zpl_opts& options);
        ~Game();

        [[nodiscard]] KML_FORCEINLINE ConfigEngine& GetEngineConfig() noexcept { return m_engineConfig; }
        [[nodiscard]] KML_FORCEINLINE const ConfigEngine& GetEngineConfig() const noexcept { return m_engineConfig; }

        [[nodiscard]] KML_FORCEINLINE ConfigClient& GetClientConfig() noexcept { return m_clientConfig; }
        [[nodiscard]] KML_FORCEINLINE const ConfigClient& GetClientConfig() const noexcept { return m_clientConfig; } 
    };
}

#endif //KMLENGINE_CLIENT_GAME_HPP

//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Window.cpp
//------------------------------------------------------------

#include "Window.hpp"
#include "../../../Common/Core/Event/EventBus.hpp"
#include "../Input/Input.hpp"
#include <SDL2/SDL_syswm.h>
#include <fmt/format.h>
#include <stdexcept>

namespace KMLEngine {
	template<> Window* Singleton<Window>::_INSTANCE = nullptr;
	Window::Window(u32 width, u32 height, bool fullscreen, const char* title) {
		KML_ASSERT(width);
		KML_ASSERT(height);
		KML_ASSERT(title);

		if(SDL_Init(SDL_INIT_VIDEO) != 0) throw std::runtime_error(fmt::format("{} failed: {}", "SDL_Init", SDL_GetError()));

		u32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN;
		if(fullscreen) flags |= SDL_WINDOW_FULLSCREEN;

		m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, static_cast<i32>(width), static_cast<i32>(height), flags);
		if(!m_window) throw std::runtime_error(fmt::format("{} failed: {}", "SDL_CreateWindow", SDL_GetError()));

		m_isCloseRequested = false;

		SDL_SysWMinfo sysWMInfo;
		SDL_VERSION(&sysWMInfo.version);
		if(!SDL_GetWindowWMInfo(m_window, &sysWMInfo)) throw std::runtime_error(fmt::format("{} failed: {}", "SDL_GetWindowWMInfo", SDL_GetError()));

#ifdef KML_PLATFORM_WINDOWS
		m_platformHandle = sysWMInfo.info.win.window;
#elif defined(KML_PLATFORM_MACOS)
		m_platformHandle = sysWMInfo.info.cocoa.window;
#elif defined(KML_PLATFORM_LINUX)
		m_platformHandle = reinterpret_cast<void*>(sysWMInfo.info.x11.window);
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
		AttachSingleton();
	}
	
	Window::~Window() {
		DetachSingleton();

		SDL_DestroyWindow(m_window);
		m_window = nullptr;

		m_pressedKeys.clear();
		m_isCloseRequested = false;
		m_platformHandle = nullptr;
	}
	
	void Window::ProcessEvents(EventBus& eventBus) {
		SDL_Event event;

		while(SDL_PollEvent(&event)) {
			eventBus.PostEmplace<SystemEvent>(event);
			switch(event.type) {
			case SDL_QUIT:
				m_isCloseRequested = true;
				break;
			case SDL_WINDOWEVENT: {
				switch(event.window.event) {
				case SDL_WINDOWEVENT_SIZE_CHANGED: {
					const auto size = GetSize();

					eventBus.PostEmplace<WindowResizeEvent>(size.X, size.Y);
					break;
				}
				case SDL_WINDOWEVENT_MOVED: {
					const auto position = GetPosition();

					eventBus.PostEmplace<WindowMoveEvent>(position.X, position.Y);
					break;
				}
				case SDL_WINDOWEVENT_MINIMIZED:
					eventBus.PostEmplace<WindowMinimizeEvent>();
					break;
				case SDL_WINDOWEVENT_MAXIMIZED:
					eventBus.PostEmplace<WindowMaximizeEvent>();
					break;
				default:
					break;
				}
			}
			break;
			case SDL_KEYDOWN: {
				const auto key = static_cast<EKeys>(event.key.keysym.scancode);

				eventBus.PostEmplace<KeyDownEvent>(key);

				if(m_pressedKeys.find(key) == m_pressedKeys.end()) {
					eventBus.PostEmplace<KeyPressEvent>(key);
					m_pressedKeys.insert(key);
				}
			}

			break;
			case SDL_KEYUP: {
				const auto key = static_cast<EKeys>(event.key.keysym.scancode);

				eventBus.PostEmplace<KeyUpEvent>(key);

				const auto iterator = m_pressedKeys.find(key);
				if(iterator != m_pressedKeys.end()) {
					eventBus.PostEmplace<KeyReleaseEvent>(key);
					m_pressedKeys.erase(iterator);
				}
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
				eventBus.PostEmplace<MouseButtonDownEvent>(static_cast<EMouseButton>(event.button.button - 1), event.button.x, event.button.y);
				break;
			case SDL_MOUSEBUTTONUP:
				eventBus.PostEmplace<MouseButtonUpEvent>(static_cast<EMouseButton>(event.button.button - 1), event.button.x, event.button.y);
				break;
			case SDL_MOUSEMOTION:
				eventBus.PostEmplace<MouseMotionEvent>(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
				break;
			case SDL_MOUSEWHEEL:
				eventBus.PostEmplace<MouseScrollEvent>(event.wheel.x, event.wheel.y);
				break;
			default:
				break;
			}
		}

		Input::Refresh();
	}
}


//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Window.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_CORE_WINDOW_WINDOW_HPP
#define KMLENGINE_CLIENT_CORE_WINDOW_WINDOW_HPP

#pragma once

#include "../../../Platform/Types.hpp"
#include "../../../Common/Util/Traits/Disposable.hpp"
#include "../../../Common/Util/Traits/Singleton.hpp"
#include "../../../Common/Util/Math/Point.hpp"
#include "../../../Common/Util/STL/flat_hash_set.hpp"
#include "../Input/Keys.hpp"
#include <SDL2/SDL.h>

namespace KMLEngine {
	class EventBus;
	class Window final : public Uncopyable, public Singleton<Window> {
	private:
		SDL_Window* m_window = nullptr;
		void* m_platformHandle = nullptr;
		bool m_isCloseRequested = false;
		kml_stl::flat_hash_set<EKeys> m_pressedKeys;

	public:
		Window(u32 width, u32 height, bool fullscreen, const char* title);
		~Window();
		
		void ProcessEvents(EventBus& eventBus);

		KML_FORCEINLINE void SetX(i32 x) noexcept {
			i32 y;
			SDL_GetWindowPosition(m_window, nullptr, &y);
			SDL_SetWindowPosition(m_window, x, y);
		}

		KML_FORCEINLINE void SetY(i32 y) noexcept {
			i32 x;
			SDL_GetWindowPosition(m_window, &x, nullptr);
			SDL_SetWindowPosition(m_window, x, y);
		}

		KML_FORCEINLINE void SetPosition(const PointI32& position) noexcept {
			SDL_SetWindowPosition(m_window, position.X, position.Y);
		}

		KML_FORCEINLINE void SetWidth(u32 width) noexcept {
			u32 height;
			SDL_GetWindowSize(m_window, nullptr, reinterpret_cast<i32*>(&height));
			SDL_SetWindowSize(m_window, static_cast<i32>(width), static_cast<i32>(height));
		}

		KML_FORCEINLINE void SetHeight(u32 height) noexcept {
			u32 width;
			SDL_GetWindowSize(m_window, reinterpret_cast<i32*>(&width), nullptr);
			SDL_SetWindowSize(m_window, static_cast<i32>(width), static_cast<i32>(height));
		}

		KML_FORCEINLINE void SetSize(const PointU32& dimension) noexcept {
			SDL_SetWindowSize(m_window, static_cast<i32>(dimension.X), static_cast<i32>(dimension.Y));
		}

		[[nodiscard]] KML_FORCEINLINE i32 GetX() const noexcept {
			i32 x;
			SDL_GetWindowPosition(m_window, &x, nullptr);
			return x;
		}

		[[nodiscard]] KML_FORCEINLINE i32 GetY() const noexcept {
			i32 y;
			SDL_GetWindowPosition(m_window, nullptr, &y);
			return y;
		}

		[[nodiscard]] KML_FORCEINLINE PointI32 GetPosition() const noexcept {
			PointI32 point;
			SDL_GetWindowPosition(m_window, &point.X, &point.Y);
			return point;
		}

		[[nodiscard]] KML_FORCEINLINE u32 GetWidth() const noexcept {
			u32 width;
			SDL_GetWindowSize(m_window, reinterpret_cast<i32*>(&width), nullptr);
			return width;
		}

		[[nodiscard]] KML_FORCEINLINE u32 GetHeight() const noexcept {
			u32 height;
			SDL_GetWindowSize(m_window, nullptr, reinterpret_cast<i32*>(&height));
			return height;
		}

		[[nodiscard]] KML_FORCEINLINE PointU32 GetSize() const noexcept {
			PointU32 size;
			SDL_GetWindowSize(m_window, reinterpret_cast<i32*>(&size.X), reinterpret_cast<i32*>(&size.Y));
			return size;
		}

		[[nodiscard]] KML_FORCEINLINE bool IsFullscreen() const noexcept {
			return (SDL_GetWindowFlags(m_window) & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN;
		}

		[[nodiscard]] KML_FORCEINLINE bool IsMinimized() const noexcept {
			return (SDL_GetWindowFlags(m_window) & SDL_WINDOW_MINIMIZED) == SDL_WINDOW_MINIMIZED;
		}

		[[nodiscard]] KML_FORCEINLINE bool IsMaximized() const noexcept {
			return (SDL_GetWindowFlags(m_window) & SDL_WINDOW_MAXIMIZED) == SDL_WINDOW_MAXIMIZED;
		}

		[[nodiscard]] KML_FORCEINLINE bool HasMouseFocus() const noexcept {
			return (SDL_GetWindowFlags(m_window) & SDL_WINDOW_MOUSE_FOCUS) == SDL_WINDOW_MOUSE_FOCUS;
		}

		[[nodiscard]] KML_FORCEINLINE bool IsCloseRequested() const noexcept { return m_isCloseRequested; }

		KML_FORCEINLINE void SetCloseRequested() noexcept { m_isCloseRequested = true; }

		[[nodiscard]] KML_FORCEINLINE void* GetPlatformHandle() const noexcept { return m_platformHandle; }
		[[nodiscard]] KML_FORCEINLINE SDL_Window* GetHandle() { return m_window; }
	};
}

#endif //KMLENGINE_CLIENT_CORE_WINDOW_WINDOW_HPP

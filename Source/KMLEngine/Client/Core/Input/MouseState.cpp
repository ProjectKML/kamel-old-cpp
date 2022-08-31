//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: MouseState.cpp
//------------------------------------------------------------

#include "MouseState.hpp"
#include "../Window/Window.hpp"
#include <SDL2/SDL.h>

namespace KMLEngine {
	MouseState MouseState::Get() noexcept {
		auto& window = Window::GetInstance();

		i32 globalX, globalY;
		const auto state = SDL_GetGlobalMouseState(&globalX, &globalY);
		return MouseState(state, globalX - window.GetX(), globalY - window.GetY());
	}

	bool MouseState::IsButtonDown(EMouseButton button) const noexcept { return (m_state & SDL_BUTTON(static_cast<i32>(button) + 1)); }
	bool MouseState::IsButtonUp(EMouseButton button) const noexcept { return (m_state & SDL_BUTTON(static_cast<i32>(button) + 1)) == 0; }
}

//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Mouse.cpp
//------------------------------------------------------------

#include "Mouse.hpp"
#include "../Window/Window.hpp"
#include <SDL2/SDL.h>

namespace KMLEngine::Mouse {
    void SetPosition(const PointI32& position) noexcept { 
        SDL_WarpMouseGlobal(position.X, position.Y);
    }
    void SetPosition(Window& window, const PointI32& position) noexcept {
        SDL_WarpMouseGlobal(window.GetX() + position.X, window.GetY() + position.Y);
    }
    void SetPositionCentered(Window& window) noexcept {
        SDL_WarpMouseGlobal(window.GetX() + (window.GetWidth() >> 1), window.GetY() + (window.GetHeight() >> 1));
    }
}

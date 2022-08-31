//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: KeyboardState.cpp
//------------------------------------------------------------

#include "KeyboardState.hpp"
#include <SDL2/SDL.h>

namespace KMLEngine {
    KeyboardState::KeyboardState(const u8* data) noexcept {
        for(auto ix = 0; ix < NUM_KEYS; ix++) {
            m_pressedKeys.set(ix, data[ix]);
        }
    }

    KeyboardState KeyboardState::Get() noexcept { return KeyboardState(SDL_GetKeyboardState(nullptr)); }
}

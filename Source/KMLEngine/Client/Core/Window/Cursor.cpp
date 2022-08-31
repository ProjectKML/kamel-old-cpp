//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Cursor.cpp
//------------------------------------------------------------

#include "Cursor.hpp"
#include "../../../Common/Core/Package/PackageLocation.hpp"
#include <fmt/format.h>

namespace KMLEngine {

    void Cursor::OnDisposing() noexcept {
        SDL_FreeCursor(m_cursor);

        m_cursor = nullptr;
    }

    void Cursor::Create(const PackageLocation& location, i32 hotX, i32 hotY) {
        std::vector<byte> buffer;
        location.GetEntry(buffer);

        auto* surface = SDL_LoadBMP_RW(SDL_RWFromMem(buffer.data(), static_cast<i32>(buffer.size())), 1);
        if(!surface) {
            throw std::runtime_error(fmt::format("Failed to load cursor: {}", location.ToString()));
        }

        m_cursor = SDL_CreateColorCursor(surface, hotX, hotY);
        SDL_FreeSurface(surface);

        if(!m_cursor) {
            throw std::runtime_error(fmt::format("Failed to create cursor: {}", SDL_GetError()));
        }
        
        SetInitialized();
    }

    void Cursor::SetCurrent() noexcept { SDL_SetCursor(m_cursor); }
    void Cursor::Enable() noexcept { SDL_ShowCursor(SDL_ENABLE); }
    void Cursor::Disable() noexcept { SDL_ShowCursor(SDL_DISABLE); }
}

//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Cursor.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_CORE_WINDOW_CURSOR_HPP
#define KMLENGINE_CLIENT_CORE_WINDOW_CURSOR_HPP

#pragma once

#include "../../../Common/Util/Traits/Disposable.hpp"
#include <SDL2/SDL.h>

namespace KMLEngine {
    class PackageLocation;
    class Cursor final : public Disposable<Cursor> {
        friend Disposable<Cursor>;
    private:
        SDL_Cursor* m_cursor = nullptr;

        void OnDisposing() noexcept;
    public:
        void Create(const PackageLocation& location, i32 hotX, i32 hotY);

        void SetCurrent() noexcept;

        static void Enable() noexcept;
        static void Disable() noexcept;
    };
}

#endif //KMLENGINE_CLIENT_CORE_WINDOW_CURSOR_HPP
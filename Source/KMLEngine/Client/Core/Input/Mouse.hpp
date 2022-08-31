//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Mouse.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_CORE_INPUT_MOUSE_HPP
#define KMLENGINE_CLIENT_CORE_INPUT_MOUSE_HPP

#pragma once

#include "../../../Common/Util/Math/Point.hpp"

namespace KMLEngine {
    class Window;
    namespace Mouse {
        void SetPosition(const PointI32& position) noexcept;
        void SetPosition(Window& window, const PointI32& position) noexcept;

        void SetPositionCentered(Window& window) noexcept;
    }
}

#endif //KMLENGINE_CLIENT_CORE_INPUT_MOUSE_HPP

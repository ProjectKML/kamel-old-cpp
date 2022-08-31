//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: MouseButton.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_CORE_INPUT_MOUSEBUTTON_HPP
#define KMLENGINE_CLIENT_CORE_INPUT_MOUSEBUTTON_HPP

#pragma once

#include "../../../Platform/Types.hpp"

namespace KMLEngine {
    enum class EMouseButton : u32 {
        Left = 0,
        Middle = 1,
        Right = 2,
        X1 = 3,
        X2 = 4
    };

    namespace MouseButton {
        [[nodiscard]] const char* GetName(EMouseButton button) noexcept;
    }
}

#endif //KMLENGINE_CLIENT_CORE_INPUT_MOUSEBUTTON_HPP

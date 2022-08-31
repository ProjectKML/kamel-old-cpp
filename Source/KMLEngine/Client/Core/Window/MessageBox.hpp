//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: MessageBox.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_CORE_WINDOW_MESSAGEBOX_HPP
#define KMLENGINE_CLIENT_CORE_WINDOW_MESSAGEBOX_HPP

#pragma once

#include <string_view>

namespace KMLEngine {
    class Window;
    namespace MessageBox {
        enum class Type {
            Information = 0,
            Warning = 1,
            Error = 2
        };
        
        void Show(Type type, const std::string_view& title, const std::string_view& message, Window* window = nullptr);
    }
}

#endif //KMLENGINE_CLIENT_CORE_WINDOW_MESSAGEBOX_HPP

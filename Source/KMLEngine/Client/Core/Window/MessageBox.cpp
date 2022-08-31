//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: MessageBox.cpp
//------------------------------------------------------------

#include "MessageBox.hpp"

#ifdef KML_PLATFORM_WINDOWS
#include "../../../Common/Util/String/String.hpp"
#include <Windows.h>
#undef MessageBox
#elif defined(KML_PLATFORM_LINUX) || defined(KML_PLATFORM_MACOS)
#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
#include "Window.hpp"

namespace KMLEngine {

    void MessageBox::Show(Type type, const std::string_view& title, const std::string_view& message, Window* window) {
#ifdef KML_PLATFORM_WINDOWS
        const auto titleW = String::ToUTF16(title);
        const auto messageW = String::ToUTF16(message);

        UINT icon;
        switch (type) {
            case Type::Warning: icon = MB_ICONWARNING; break;
            case Type::Error: icon = MB_ICONERROR; break;
            default: icon = MB_ICONINFORMATION; break;
        }
        
        MessageBoxW(window ? static_cast<HWND>(window->GetPlatformHandle()) : nullptr, messageW.data(), titleW.data(), MB_OK | icon);
#elif defined(KML_PLATFORM_LINUX) || defined(KML_PLATFORM_MACOS)
        u32 flags;
        switch (type) {
            case Type::Information: flags = SDL_MESSAGEBOX_INFORMATION; break;
            case Type::Warning: flags = SDL_MESSAGEBOX_WARNING; break;
            case Type::Error: flags = SDL_MESSAGEBOX_ERROR; break;
            default: flags = SDL_MESSAGEBOX_INFORMATION; break;
        }

        if(const auto result = SDL_ShowSimpleMessageBox(flags, title.data(), message.data(), window ? window->GetHandle() : nullptr); result != 0) {
            spdlog::error("{} failed: {}. Title: {} Message: {}", "SDL_ShowSimpleMessageBox", SDL_GetError(), title.data(), message.data());
        }
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
    }
}

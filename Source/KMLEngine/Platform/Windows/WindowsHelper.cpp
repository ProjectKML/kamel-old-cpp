//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: WindowsHelper.cpp
//------------------------------------------------------------

#ifdef KML_PLATFORM_WINDOWS

#include "WindowsHelper.hpp"
#include "../../Common/Util/String/String.hpp"

#include <Windows.h>

namespace KMLEngine::WindowsHelper {
    void EnableUTF8Support() noexcept {
        SetConsoleOutputCP(CP_UTF8);
    }

    std::string GetLastErrorAsString() noexcept {
        const auto errorMessageId = GetLastError();
        if(errorMessageId == 0) return std::string("No error has been recorded");
        LPWSTR messageBuffer = nullptr;

        const auto size = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                         nullptr, errorMessageId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPWSTR>(&messageBuffer), 0, nullptr);

        const auto message = String::ToUTF8(messageBuffer);
        LocalFree(messageBuffer);

        return message;
    }
}

#endif

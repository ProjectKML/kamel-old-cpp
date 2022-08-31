//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ThreadExtensions.cpp
//------------------------------------------------------------

#include "ThreadExtensions.hpp"

#ifdef KML_PLATFORM_WINDOWS
#include "../String/String.hpp"
#include <Windows.h>
#elif defined(KML_PLATFORM_MACOS) || defined(KML_PLATFORM_IOS) || defined(KML_PLATFORM_LINUX)
#include <pthread.h>
#else
#error KML_UNSUPPORTED_PLATFORM
#endif

namespace KMLEngine::ThreadExtensions {
    std::string GetCurrentThreadName() noexcept{
#ifdef KML_PLATFORM_WINDOWS
        PWSTR buffer;
        if(FAILED(GetThreadDescription(GetCurrentThread(), &buffer))) return "Unknown";

        auto name = String::ToUTF8(buffer);
        LocalFree(buffer);
        return name;
#elif defined(KML_PLATFORM_MACOS) || defined(KML_PLATFORM_IOS) || defined(KML_PLATFORM_LINUX)
        char buffer[1024];
        if(pthread_getname_np(pthread_self(), buffer, sizeof(buffer)) != 0) return "Unknown";
        return buffer;
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
    }

    void SetCurrentThreadName(const std::string& name) noexcept {
#ifdef KML_PLATFORM_WINDOWS
        const auto nameW = String::ToUTF16(name);
        SetThreadDescription(GetCurrentThread(), nameW.data());
#elif defined(KML_PLATFORM_MACOS) || defined(KML_PLATFORM_IOS)
        pthread_setname_np(name.c_str());
#elif defined(KML_PLATFORM_LINUX)
        pthread_setname_np(pthread_self(), name.c_str());
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
    }
}

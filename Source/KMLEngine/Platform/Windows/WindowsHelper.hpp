//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: WindowsHelper.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_PLATFORM_WINDOWS_WINDOWSHELPER_HPP
#define KMLENGINE_PLATFORM_WINDOWS_WINDOWSHELPER_HPP

#pragma once

#ifdef KML_PLATFORM_WINDOWS

#include <string>

namespace KMLEngine::WindowsHelper {
    void EnableUTF8Support() noexcept;
    [[nodiscard]] std::string GetLastErrorAsString() noexcept;
}

#endif

#endif //KMLENGINE_PLATFORM_WINDOWS_WINDOWSHELPER_HPP

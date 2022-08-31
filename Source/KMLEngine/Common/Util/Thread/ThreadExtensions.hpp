//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ThreadExtensions.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_THREAD_THREADEXTENSIONS_HPP
#define KMLENGINE_COMMON_UTIL_THREAD_THREADEXTENSIONS_HPP

#pragma once

#include <string>

namespace KMLEngine::ThreadExtensions {
    [[nodiscard]] std::string GetCurrentThreadName() noexcept;
    void SetCurrentThreadName(const std::string& name) noexcept;
}

#endif //KMLENGINE_COMMON_UTIL_THREAD_THREADEXTENSIONS_HPP

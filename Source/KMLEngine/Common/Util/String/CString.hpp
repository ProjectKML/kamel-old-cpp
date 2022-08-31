//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: CString.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_STRING_CSTRING_HPP
#define KMLENGINE_COMMON_UTIL_STRING_CSTRING_HPP

#pragma once

#include "../../../Platform/Types.hpp"
#include "../../../Platform/Hints/ForceInline.hpp"
#include <cstring>
#include <type_traits>

namespace KMLEngine::CString {
    template<typename T> requires(std::is_same_v<T, char> || std::is_same_v<T, wchar_t>)
    [[nodiscard]] KML_FORCEINLINE usize GetLength(const T* str) noexcept {
        if constexpr(std::is_same_v<T, char>) return strlen(str);
        else if constexpr(std::is_same_v<T, wchar_t>) return wcslen(str);
    }

    template<typename T> requires(std::is_same_v<T, char> || std::is_same_v<T, wchar_t>)
    [[nodiscard]] KML_FORCEINLINE bool AreStringsEqual(const T* str1, const T* str2) noexcept {
        if constexpr(std::is_same_v<T, char>) return strcmp(str1, str2) == 0;
        else if constexpr(std::is_same_v<T, wchar_t>) return wcscmp(str1, str2) == 0;
    }
}

#endif //KMLENGINE_COMMON_UTIL_STRING_CSTRING_HPP

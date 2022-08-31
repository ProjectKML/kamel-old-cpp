//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Character.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_STRING_CHARACTER_HPP
#define KMLENGINE_COMMON_UTIL_STRING_CHARACTER_HPP

#pragma once

#include "../../../Platform/Types.hpp"
#include "../../../Platform/Hints/ForceInline.hpp"
#include "../../../Platform/Assert/Assert.hpp"

namespace KMLEngine::Character {
    [[nodiscard]] KML_FORCEINLINE char FromHexInt(byte value) noexcept {
        KML_ASSERT(value < 16);
        return value < 10 ? '0' + value : 'a' + value - 10;
    }

    [[nodiscard]] KML_FORCEINLINE byte ToHexInt(char c) noexcept {
        KML_ASSERT((c >= 'a' && c <= 'f') || (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'));
        return c <= '9' ? c - '0' : c - 'a' + 10;
    }

    [[nodiscard]] KML_FORCEINLINE byte ToHexInt(char left, char right) noexcept {
        return (ToHexInt(left) << 4) | ToHexInt(right);
    }

    [[nodiscard]] KML_FORCEINLINE bool TryToHexInt(char c, byte& result) noexcept {
        if(!(c >= 'a' && c <= 'f') && !(c >= '0' && c <= '9') && !(c >= 'A' && c <= 'F')) return false;
        result = c <= '9' ? c - '0' : (c >= 'A' && c <= 'F' ? c - 'A' + 10 : c - 'a' + 10);
        return true;
    }

    [[nodiscard]] KML_FORCEINLINE bool TryToHexInt(char left, char right, byte& result) noexcept {
        byte leftValue, rightValue;
        if(!TryToHexInt(left, leftValue)) return false;
        if(!TryToHexInt(right, rightValue)) return false;

        result = (leftValue << 4) | rightValue;

        return true;
    }

    [[nodiscard]] KML_FORCEINLINE bool IsWhitespace(char c) noexcept { return c == ' ' || c == '\r' || c == '\t'; }
    [[nodiscard]] KML_FORCEINLINE bool IsNewLine(char c) noexcept { return c == '\n'; }
    [[nodiscard]] KML_FORCEINLINE bool IsExponent(char c) noexcept { return c == 'e' || c == 'E'; }
    [[nodiscard]] KML_FORCEINLINE bool IsDigit(char c) noexcept { return c >= '0' && c <= '9'; }
}

#endif //KMLENGINE_COMMON_UTIL_STRING_CHARACTER_HPP

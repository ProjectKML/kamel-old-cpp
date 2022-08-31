//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Types.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_PLATFORM_TYPES_HPP
#define KMLENGINE_PLATFORM_TYPES_HPP

#pragma once

#include <cstdint>

namespace KMLEngine {
    static_assert(sizeof(bool) == 1, "sizeof(bool) must be 1 byte");

    using u8 = uint8_t;
    static_assert(sizeof(u8) == 1, "sizeof(u8) must be 1 byte");
    using byte = u8;

    using i8 = int8_t;
    static_assert(sizeof(i8) == 1, "sizeof(i8) must be 1 byte");

    using u16 = uint16_t;
    static_assert(sizeof(u16) == 2, "sizeof(u16) must be 2 bytes");

    using i16 = int16_t;
    static_assert(sizeof(i16) == 2, "sizeof(i16) must be 2 bytes");

    using u32 = uint32_t;
    static_assert(sizeof(u32) == 4, "sizeof(u32) must be 4 bytes");
    using bool32 = u32;

    using i32 = int32_t;
    static_assert(sizeof(i32) == 4, "sizeof(i32) must be 4 bytes");

    using u64 = uint64_t;
    static_assert(sizeof(u64) == 8, "sizeof(u64) must be 8 bytes");

    using i64 = int64_t;
    static_assert(sizeof(i64) == 8, "sizeof(i64) must be 8 bytes");

    using f32 = float;
    static_assert(sizeof(f32) == 4, "sizeof(f32) must be 4 bytes");

    using f64 = double;
    static_assert(sizeof(f64) == 8, "sizeof(f64) must be 8 bytes");

    using usize = decltype(sizeof(void*));
    static_assert(sizeof(usize) == sizeof(void*), "usize must be equal to pointer size");

    using isize = int64_t;
    static_assert(sizeof(isize) == sizeof(void*), "isize must be equal to pointer size");

    static_assert(sizeof(void*) == 8, "Only 64 bit operating systems are supported");
    static_assert(sizeof(bool) == 1, "sizeof(bool) must be 1 byte");
}

#endif //KMLENGINE_PLATFORM_TYPES_HPP
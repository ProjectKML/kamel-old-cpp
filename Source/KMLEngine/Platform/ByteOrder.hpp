//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ByteOrder.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_PLATFORM_BYTEORDER_HPP
#define KMLENGINE_PLATFORM_BYTEORDER_HPP

#pragma once

#include "Types.hpp"
#include "Hints/ForceInline.hpp"
#include <type_traits>

#ifdef KML_PLATFORM_WINDOWS
#include <cstdlib>
#elif defined(KML_PLATFORM_MACOS) || defined(KML_PLATFORM_IOS)
#include <libkern/OSByteOrder.h>
#endif

namespace KMLEngine::ByteOrder {
	[[nodiscard]] KML_FORCEINLINE u16 FlipU16(u16 value) noexcept {
#ifdef KML_PLATFORM_WINDOWS
#ifdef KML_COMPILER_MSVC
		return _byteswap_ushort(value);
#else
        return __builtin_bswap16(value);
#endif
#elif defined(KML_PLATFORM_MACOS) || defined(KML_PLATFORM_IOS)
        return OSSwapInt16(value);
#elif defined(KML_PLATFORM_LINUX)
        return __builtin_bswap16(value);
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
	}

	[[nodiscard]] KML_FORCEINLINE i16 FlipI16(i16 value) noexcept {
		auto result = FlipU16(*reinterpret_cast<u16*>(&value));
		return *reinterpret_cast<i16*>(&result);
	}

	[[nodiscard]] KML_FORCEINLINE u32 FlipU32(u32 value) noexcept {
#ifdef KML_PLATFORM_WINDOWS
#ifdef KML_COMPILER_MSVC
		return _byteswap_ulong(value);
#else
        return __builtin_bswap32(value);
#endif
#elif defined(KML_PLATFORM_MACOS) || defined(KML_PLATFORM_IOS)
        return OSSwapInt32(value);
#elif defined(KML_PLATFORM_LINUX)
        return __builtin_bswap32(value);
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
	}

	[[nodiscard]] KML_FORCEINLINE i32 FlipI32(i32 value) noexcept {
		auto result = FlipU32(*reinterpret_cast<u32*>(&value));
		return *reinterpret_cast<i32*>(&result);
	}

	[[nodiscard]] KML_FORCEINLINE u64 FlipU64(u64 value) noexcept {
#ifdef KML_PLATFORM_WINDOWS
#ifdef KML_COMPILER_MSVC
		return _byteswap_uint64(value);
#else
        return __builtin_bswap64(value);
#endif
#elif defined(KML_PLATFORM_MACOS) || defined(KML_PLATFORM_IOS)
        return OSSwapInt64(value);
#elif defined(KML_PLATFORM_LINUX)
        return __builtin_bswap64(value);
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
	}

	[[nodiscard]] KML_FORCEINLINE i64 FlipI64(i64 value) noexcept {
		auto result = FlipU64(*reinterpret_cast<u64*>(&value));
		return *reinterpret_cast<i64*>(&result);
	}

	[[nodiscard]] KML_FORCEINLINE f32 FlipF32(f32 value) noexcept {
		auto result = FlipU32(*reinterpret_cast<u32*>(&value));
		return *reinterpret_cast<f32*>(&result);
	}

	[[nodiscard]] KML_FORCEINLINE f64 FlipF64(f64 value) noexcept {
		auto result = FlipU64(*reinterpret_cast<u64*>(&value));
		return *reinterpret_cast<f64*>(&result);
	}

	template<typename T>
	[[nodiscard]] KML_FORCEINLINE T Flip(T value) noexcept {
		if constexpr(std::is_same_v<T, u16>) return FlipU16(value);
		if constexpr(std::is_same_v<T, i16>) return FlipI16(value);
		if constexpr(std::is_same_v<T, u32>) return FlipU32(value);
		if constexpr(std::is_same_v<T, i32>) return FlipI32(value);
		if constexpr(std::is_same_v<T, u64>) return FlipU64(value);
		if constexpr(std::is_same_v<T, i64>) return FlipI64(value);
		if constexpr(std::is_same_v<T, f32>) return FlipF32(value);
		if constexpr(std::is_same_v<T, f64>) return FlipF64(value);
		else return static_cast<T>(value);
	}
}

#endif //KMLENGINE_PLATFORM_BYTEORDER_HPP

//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: PlatformMemory.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_PLATFORM_PLATFORMMEMORY_HPP
#define KMLENGINE_PLATFORM_PLATFORMMEMORY_HPP

#pragma once

#include "Types.hpp"
#include "Hints/ForceInline.hpp"
#include "Assert/Assert.hpp"
#include <cstdlib>
#include <cstring>

namespace KMLEngine::PlatformMemory {
    KML_FORCEINLINE void Copy(void* destination, const void* source, usize length) noexcept {
        KML_ASSERT(destination);
        KML_ASSERT(source);
        KML_ASSERT(length);

        memcpy(destination, source, length);
    }

    KML_FORCEINLINE void Move(void* destination, const void* source, usize length) noexcept {
        KML_ASSERT(destination);
        KML_ASSERT(source);
        KML_ASSERT(length);

        memmove(destination, source, length);
    }

    KML_FORCEINLINE void Set(void* destination, u8 value, usize length) noexcept {
        KML_ASSERT(destination);
        KML_ASSERT(length);

        memset(destination, static_cast<i32>(value), length);
    }

    KML_FORCEINLINE void Zero(void* destination, usize length) noexcept {
        KML_ASSERT(destination);
        Set(destination, 0, length);
    }

    KML_FORCEINLINE i32 Compare(const void* data1, const void* data2, usize length) noexcept {
        KML_ASSERT(data1);
        KML_ASSERT(data2);
        KML_ASSERT(length);

        return memcmp(data1, data2, length);
    }

    KML_FORCEINLINE bool IsEqual(const void* data1, const void* data2, usize length) noexcept {
        return Compare(data1, data2, length) == 0;
    }

    //Allocate
    KML_FORCEINLINE void* Allocate(usize size) noexcept {
        return malloc(size);
    }

    KML_FORCEINLINE void Deallocate(void* data) noexcept { free(data); }

    KML_FORCEINLINE void* AllocateAligned(usize size, usize alignment) noexcept {
        KML_ASSERT(alignment);

#if defined(KML_PLATFORM_MACOS) || defined(KML_PLATFORM_IOS)
        if (alignment < sizeof(void*)) alignment = sizeof(void*);
#endif

#ifdef KML_PLATFORM_WINDOWS
        return _aligned_malloc(size, alignment);
#elif defined(KML_PLATFORM_MACOS) || defined(KML_PLATFORM_IOS) || defined(KML_PLATFORM_LINUX)
        return aligned_alloc(alignment, size);
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
    }

    KML_FORCEINLINE void DeallocateAligned(void* data) noexcept {
#ifdef KML_PLATFORM_WINDOWS
        _aligned_free(data);
#elif defined(KML_PLATFORM_MACOS) || defined(KML_PLATFORM_IOS) || defined(KML_PLATFORM_LINUX)
        free(data);
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
    }

    KML_FORCEINLINE void* Reallocate(void* oldData, usize newSize) noexcept {
        return realloc(oldData, newSize);
    }

    KML_FORCEINLINE void* ReallocateAligned(void* oldData, usize newSize, usize alignment) noexcept {
        KML_ASSERT(alignment);

#ifdef KML_PLATFORM_WINDOWS
        return _aligned_realloc(oldData, newSize, alignment);
#elif defined(KML_PLATFORM_MACOS) || defined(KML_PLATFORM_IOS) || defined(KML_PLATFORM_LINUX)
        auto* newData = AllocateAligned(newSize, alignment);
		Copy(newData, oldData, newSize);
		DeallocateAligned(oldData);
		return newData;
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
    }
}

#endif //KMLENGINE_PLATFORM_PLATFORMMEMORY_HPP

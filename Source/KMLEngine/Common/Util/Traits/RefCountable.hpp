//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RefCountable.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_TRAITS_REFCOUNTABLE_HPP
#define KMLENGINE_COMMON_UTIL_TRAITS_REFCOUNTABLE_HPP

#pragma once

#include "../../../Platform/Types.hpp"
#include "../../../Platform/Hints/ForceInline.hpp"
#include <atomic>

namespace KMLEngine
{
    class RefCountable
    {
    protected:
        mutable std::atomic_uint32_t m_refCount;
    public:
        RefCountable() noexcept = default;
        
        KML_FORCEINLINE void IncrementRef() const noexcept { ++m_refCount; }
        KML_FORCEINLINE void DecrementRef() const noexcept { --m_refCount; }

        [[nodiscard]] KML_FORCEINLINE u32 GetRefCount() const noexcept { return m_refCount; }
    };
}

#endif //KMLENGINE_COMMON_UTIL_TRAITS_REFCOUNTABLE_HPP
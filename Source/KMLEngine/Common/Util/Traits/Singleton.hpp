//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Singleton.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_TRAITS_SINGLETON_HPP
#define KMLENGINE_COMMON_UTIL_TRAITS_SINGLETON_HPP

#pragma once

#include "../../../Platform/Assert/Assert.hpp"
#include "../../../Platform/Hints/ForceInline.hpp"

namespace KMLEngine {
    template<typename T>
    class Singleton {
    private:
        static T* _INSTANCE;
    protected:
        KML_FORCEINLINE void AttachSingleton() noexcept {
            KML_ASSERT(!_INSTANCE  && "Singleton has already been attached");
            _INSTANCE = static_cast<T*>(this);
        }

        KML_FORCEINLINE void DetachSingleton() noexcept {
            KML_ASSERT(_INSTANCE && "Singleton has not been attached");
            _INSTANCE = nullptr;
        }
    public:
        Singleton() noexcept = default;
    public:        
        [[nodiscard]] static T& GetInstance() noexcept {
            KML_ASSERT(_INSTANCE && "Singleton has not been attached");
            return *_INSTANCE;
        }

        [[nodiscard]] static T* TryGetInstance() noexcept { return _INSTANCE; }
    };
}

#endif //KMLENGINE_COMMON_UTIL_TRAITS_SINGLETON_HPP

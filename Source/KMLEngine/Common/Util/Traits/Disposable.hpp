//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Disposable.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_TRAITS_DISPOSABLE_HPP
#define KMLENGINE_COMMON_UTIL_TRAITS_DISPOSABLE_HPP

#pragma once

#include "../../../Platform/Types.hpp"
#include "../../../Platform/Hints/ForceInline.hpp"
#include "../../../Platform/Assert/Assert.hpp"
#include "Uncopyable.hpp"
#include <utility>

namespace KMLEngine {
    template<typename T, typename... Arguments>
    class DisposableWithArguments : public Uncopyable {
    protected:
        bool32 m_isInitialized = false;

        KML_FORCEINLINE void SetInitialized() {
            KML_ASSERT(!m_isInitialized && "Disposable has already been initialized");
            m_isInitialized = true;
        }
    public:
        DisposableWithArguments() noexcept = default;

        ~DisposableWithArguments() noexcept {
            KML_ASSERT(!m_isInitialized && "Disposable has not been initialized");
        }

        void Dispose(Arguments... arguments) {
            KML_ASSERT(m_isInitialized && "Disposable has not been initialized");
            static_cast<T*>(this)->OnDisposing(std::forward<Arguments>(arguments)...);
            m_isInitialized = false;
        }

        [[nodiscard]] KML_FORCEINLINE bool32 IsInitialized() const noexcept { return m_isInitialized; }
    };

    template<typename T>
    using Disposable = DisposableWithArguments<T>;
}

#endif //KMLENGINE_COMMON_UTIL_TRAITS_DISPOSABLE_HPP

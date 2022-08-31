//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Ref.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_REF_HPP
#define KMLENGINE_COMMON_UTIL_REF_HPP

#pragma once

#include "../../Platform/Assert/Assert.hpp"
#include "Traits/RefCountable.hpp"
#include <type_traits>

namespace KMLEngine {
    template<typename T>
    class Ref final {
    private:
        mutable T* m_instance;

        explicit Ref(T* instance) : m_instance(instance) {
            static_assert(std::is_base_of<RefCountable, T>::value, "T must be ref countable");
            KML_ASSERT(instance);

            IncrementRef();
        }
    public:
        Ref() noexcept : m_instance(nullptr) {}
        Ref(std::nullptr_t) noexcept : m_instance(nullptr) {}

        template<typename U = T> requires(std::is_base_of_v<U, T>)
        Ref(const Ref<U>& other) noexcept : m_instance(other.m_instance) { IncrementRef(); }

        template<typename U = T> requires(std::is_base_of_v<U, T>)
        Ref(Ref<U>&& other) noexcept : m_instance(other.m_instance) { other.m_instance = nullptr; }

        Ref& operator =(std::nullptr_t) noexcept {
            if(m_instance) DecrementRef();
            m_instance = nullptr;
            
            return *this;
        }

        template<typename U> requires(std::is_base_of_v<U, T>)
        Ref& operator =(const Ref<U>& other) noexcept {
            other.IncrementRef();
            if(m_instance) DecrementRef();

            m_instance = other.m_instance;
            
            return *this;
        }

        Ref& operator =(const Ref<T>& other) noexcept {
            other.IncrementRef();
            if(m_instance) DecrementRef();

            m_instance = other.m_instance;

            return *this;
        }

        template<typename U = T> requires(std::is_base_of_v<U, T>)
        Ref& operator =(Ref<U>&& other) noexcept {
            if(m_instance) DecrementRef();

            m_instance = other.m_instance;
            other.m_instance = nullptr;

            return *this;
        }

        ~Ref() noexcept {
            if(m_instance) DecrementRef();
        }
        
        KML_FORCEINLINE void IncrementRef() const noexcept {
            KML_ASSERT(m_instance);
            m_instance->IncrementRef();
        }

        KML_FORCEINLINE void DecrementRef() const noexcept {
            KML_ASSERT(m_instance);
            m_instance->DecrementRef();
            
            if(!m_instance->GetRefCount()) {
                delete m_instance;
                m_instance = nullptr;
            }
        }

        template<typename U> requires(std::is_base_of_v<U, T>)
        Ref<U> Cast() const noexcept {
            return Ref<U>(m_instance);
        }

        [[nodiscard]] KML_FORCEINLINE T* Get() noexcept { return m_instance; }
        [[nodiscard]] KML_FORCEINLINE const T* Get() const noexcept { return m_instance; }

        KML_FORCEINLINE operator bool() const noexcept { return m_instance != nullptr; }

        [[nodiscard]] KML_FORCEINLINE T* operator ->() noexcept {
            KML_ASSERT(m_instance);
            return m_instance;
        }

        [[nodiscard]] KML_FORCEINLINE const T* operator ->() const noexcept {
            KML_ASSERT(m_instance);
            return m_instance;
        }

        [[nodiscard]] KML_FORCEINLINE T& operator *() noexcept {
            KML_ASSERT(m_instance);
            return *m_instance;
        }

        [[nodiscard]] KML_FORCEINLINE const T& operator *() const noexcept {
            KML_ASSERT(m_instance);
            return *m_instance;
        }

        [[nodiscard]] KML_FORCEINLINE T** operator &() noexcept {
            KML_ASSERT(m_instance);
            return &m_instance;
        }

        [[nodiscard]] KML_FORCEINLINE const T** operator &() const noexcept {
            KML_ASSERT(m_instance);
            return &m_instance;
        }

        template<typename U = T> requires(std::is_base_of_v<U, T>)
        [[nodiscard]] KML_FORCEINLINE bool operator ==(const Ref<U>& other) const noexcept {
            return m_instance == other.m_instance;
        }

        template<typename U = T> requires(std::is_base_of_v<U, T>)
        [[nodiscard]] KML_FORCEINLINE bool operator !=(const Ref<U>& other) const noexcept {
            return m_instance != other.m_instance;
        }
    public:
        template<typename... Arguments>
        KML_FORCEINLINE static Ref New(Arguments&&... arguments) {
            return Ref(new T(std::forward<Arguments>(arguments)...));
        }
    };
}

#endif //KMLENGINE_COMMON_UTIL_REF_HPP

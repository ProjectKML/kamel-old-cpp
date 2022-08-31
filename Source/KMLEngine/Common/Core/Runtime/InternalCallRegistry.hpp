//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: InternalCallRegistry.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_CORE_RUNTIME_INTERNALCALLREGISTRY_HPP
#define KMLENGINE_COMMON_CORE_RUNTIME_INTERNALCALLREGISTRY_HPP

#pragma once

#include "../../../Platform/Hints/ForceInline.hpp"
#include "../../../Platform/Assert/Assert.hpp"
#include <vector>

namespace KMLEngine {
    class InternalCallRegistry final {
    public:
        struct InternalCall {
            const char* Name;
            void* Function;

            InternalCall(const char* name, void* function) noexcept : Name(name), Function(function) {
                KML_ASSERT(name);
                KML_ASSERT(function);
            }
        };
    private:
        std::vector<InternalCall> m_internalCalls;

        KML_FORCEINLINE void Add(const char* name, void* function) {
            KML_ASSERT(name);
            KML_ASSERT(function);

            m_internalCalls.emplace_back(name, function);
        }

        void RegisterInternalCalls();
    public:
        InternalCallRegistry() { RegisterInternalCalls(); }

        [[nodiscard]] KML_FORCEINLINE const std::vector<InternalCall>& GetInternalCalls() const { return m_internalCalls; }
    };
}

#endif //KMLENGINE_COMMON_CORE_RUNTIME_INTERNALCALLREGISTRY_HPP
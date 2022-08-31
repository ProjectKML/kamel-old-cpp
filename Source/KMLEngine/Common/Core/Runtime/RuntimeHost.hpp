//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RuntimeHost.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_CORE_RUNTIME_RUNTIMEHOST_HPP
#define KMLENGINE_COMMON_CORE_RUNTIME_RUNTIMEHOST_HPP

#pragma once

#include "../../../Platform/Types.hpp"
#include "../../Util/Traits/Singleton.hpp"
#include "../../Util/Traits/Uncopyable.hpp"
#include "../../Util/Library/DynamicLibrary.hpp"
#include <hostfxr/hostfxr.h>
#include <hostfxr/coreclr_delegates.h>
#include <fmt/format.h>

namespace KMLEngine {
    class RuntimeHost final : public Disposable<RuntimeHost>, public Singleton<RuntimeHost> {
        friend Disposable<RuntimeHost>;
    public:
        class Exception final : public std::runtime_error {
        public:
            explicit Exception(const std::string& message) : std::runtime_error(message) {}
        };
    private:
        DynamicLibrary m_hostfxrLib;

        hostfxr_handle m_handle = nullptr;

        hostfxr_close_fn m_hostfxr_close = nullptr;
        hostfxr_get_runtime_delegate_fn m_hostfxr_get_runtime_delegate = nullptr;
        load_assembly_and_get_function_pointer_fn m_load_assembly_and_get_function_pointer = nullptr;

        void*(*m_getMethod)(const char*, const char*) = nullptr;
        void*(*m_getMethodWithParameters)(const char*, const char*, u32, const char* const*) = nullptr;

        std::filesystem::path m_assemblyPath;
    public:
        RuntimeHost();
        ~RuntimeHost();

        template<typename T = void(*)()>
        [[nodiscard]] KML_FORCEINLINE typename AddOrKeepPointer<T>::Type GetMethod(const char* typeName, const char* methodName) const {
            KML_ASSERT(typeName);
            KML_ASSERT(methodName);
            KML_ASSERT(m_getMethod);

            auto method = m_getMethod(typeName, methodName);
            if(!method) throw Exception(fmt::format("Failed to get method: {}:{}", typeName, methodName));

            return (typename AddOrKeepPointer<T>::Type)(method);
        }

        template<typename T = void(*)()>
        [[nodiscard]] KML_FORCEINLINE typename AddOrKeepPointer<T>::Type GetMethod(const char* typeName, const char* methodName, u32 numParameters, const char* const* parameters) {
            KML_ASSERT(typeName);
            KML_ASSERT(methodName);
            KML_ASSERT(parameters != nullptr || numParameters == 0);

            auto method = m_getMethodWithParameters(typeName, methodName, numParameters, parameters);
            if(!method) throw Exception(fmt::format("Failed to get method: {}:{}", typeName, methodName));

            return (typename AddOrKeepPointer<T>::Type)(method);
        }
    };
}


#endif //KMLENGINE_COMMON_CORE_RUNTIME_RUNTIMEHOST_HPP
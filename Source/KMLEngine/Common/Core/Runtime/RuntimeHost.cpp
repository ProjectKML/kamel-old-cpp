//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RuntimeHost.cpp
//------------------------------------------------------------

#include "RuntimeHost.hpp"
#include "InternalCallRegistry.hpp"
#include "../../Util/String/String.hpp"

namespace KMLEngine {
    template<> RuntimeHost* Singleton<RuntimeHost>::_INSTANCE = nullptr;

    static const char* _NET_VERSION = "6.0.0-preview.5.21301.5";

    RuntimeHost::RuntimeHost() {
        const std::filesystem::path path = std::filesystem::current_path() / "Common" / "Runtime" / "host" / "fxr" /
                                           _NET_VERSION;

        m_hostfxrLib.Create(path, "hostfxr");

        m_hostfxr_close = m_hostfxrLib.Get<hostfxr_close_fn>("hostfxr_close");

        const auto hostfxr_initialize_for_runtime_config = m_hostfxrLib.Get<hostfxr_initialize_for_runtime_config_fn>(
                "hostfxr_initialize_for_runtime_config");
        m_hostfxr_get_runtime_delegate = m_hostfxrLib.Get<hostfxr_get_runtime_delegate_fn>(
                "hostfxr_get_runtime_delegate");

        const auto configPath = std::filesystem::current_path() / "Common" / "runtimeconfig.json";

        if (const auto result = hostfxr_initialize_for_runtime_config(configPath.c_str(), nullptr, &m_handle); result != 0) {
            throw Exception(fmt::format("{} failed: {}", "hostfxr_initialize_for_runtime_config", result));
        }

        if(const auto result = m_hostfxr_get_runtime_delegate(m_handle, hdt_load_assembly_and_get_function_pointer,
                                                              reinterpret_cast<void**>(&m_load_assembly_and_get_function_pointer)); result != 0) {
            throw Exception(fmt::format("{} failed: {}", "hostfxr_get_runtime_delegate", result));
        }

        m_assemblyPath = std::filesystem::current_path() / "Common" / "KMLEngine.Managed.dll";

#ifdef KML_PLATFORM_WINDOWS
        const auto* assemblyPath = L"KMLEngine.Managed.Common.Core.Loader.NativeLoader, KMLEngine.Managed";
        const auto* methodName = L"Initialize";
#elif defined(KML_PLATFORM_LINUX) || defined(KML_PLATFORM_MACOS)
        const auto* assemblyPath = "KMLEngine.Managed.Common.Core.Loader.NativeLoader, KMLEngine.Managed";
        const auto* methodName = "Initialize";
#endif
        void(*initializeFunction)(u32, const InternalCallRegistry::InternalCall*, void**);
        if(const auto result = m_load_assembly_and_get_function_pointer(m_assemblyPath.c_str(), assemblyPath, methodName, UNMANAGEDCALLERSONLY_METHOD,
                                                                        nullptr, reinterpret_cast<void**>(&initializeFunction)); result != 0) {
            throw Exception(fmt::format("{} failed for engine assembly: {}", "load_assembly_and_get_function_pointer", result));
        }

        InternalCallRegistry registry;

        void* functions[2];
        initializeFunction(static_cast<u32>(registry.GetInternalCalls().size()), registry.GetInternalCalls().data(), functions);

        m_getMethod = (void*(*)(const char*, const char*))(functions[0]);
        m_getMethodWithParameters = (void*(*)(const char*, const char*, u32, const char* const*))(functions[1]);
    }

    RuntimeHost::~RuntimeHost() {
        m_hostfxr_close(m_handle);

        m_hostfxrLib.Dispose();

        m_getMethodWithParameters = nullptr;
        m_getMethod = nullptr;

        m_load_assembly_and_get_function_pointer = nullptr;
        m_hostfxr_get_runtime_delegate = nullptr;
        m_hostfxr_close = nullptr;

        m_handle = nullptr;
    }
}

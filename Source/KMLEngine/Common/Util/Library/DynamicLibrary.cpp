//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: DynamicLibrary.cpp
//------------------------------------------------------------

#include "DynamicLibrary.hpp"

#ifdef KML_PLATFORM_WINDOWS
#include <Windows.h>
#elif defined(KML_PLATFORM_LINUX) || defined(KML_PLATFORM_MACOS)
#include <dlfcn.h>
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
#include <fmt/format.h>
namespace KMLEngine {
    void DynamicLibrary::OnDisposing() {
#ifdef KML_PLATFORM_WINDOWS
        FreeLibrary(static_cast<HMODULE>(m_handle));
#elif defined(KML_PLATFORM_LINUX) || defined(KML_PLATFORM_MACOS)
        dlclose(m_handle);
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
        m_handle = nullptr;
    }

    void* DynamicLibrary::GetInternal(const std::string_view& name) const {
        void* result = nullptr;
#ifdef KML_PLATFORM_WINDOWS
        result = GetProcAddress(static_cast<HMODULE>(m_handle), name.data());
#elif defined(KML_PLATFORM_LINUX) || defined(KML_PLATFORM_MACOS)
        result = dlsym(m_handle, name.data());
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
        if(!result) throw Exception(fmt::format("Entry point {} in {} does not exist", name, m_path.string()));
        return result;
    }

    void DynamicLibrary::Create(const std::filesystem::path& path, const std::string_view& name) {
#ifdef KML_PLATFORM_WINDOWS
        Create(path / fmt::format("{}.dll", name));
#elif defined(KML_PLATFORM_LINUX)
        Create(path / fmt::format("lib{}.so", name));
#elif defined(KML_PLATFORM_MACOS)
        Create(path / fmt::format("lib{}.dylib", name));
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
    }

    void DynamicLibrary::Create(const std::filesystem::path& totalPath) {
        m_path = totalPath;

#ifdef KML_PLATFORM_WINDOWS
        m_handle = LoadLibraryA(totalPath.string().c_str());
#elif defined(KML_PLATFORM_LINUX) || defined(KML_PLATFORM_MACOS)
        m_handle = dlopen(totalPath.c_str(), RTLD_NOW);
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
        if(!m_handle) throw Exception(fmt::format("Failed to load dynamic library {}", totalPath.string()));

        SetInitialized();
    }
}

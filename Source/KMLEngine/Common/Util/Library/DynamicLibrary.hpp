//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: DynamicLibrary.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_LIBRARY_DYNAMICLIBRARY_HPP
#define KMLENGINE_COMMON_UTIL_LIBRARY_DYNAMICLIBRARY_HPP

#pragma once

#include "../Traits/Disposable.hpp"
#include "../Traits/AddOrKeepPointer.hpp"
#include <filesystem>
#include <stdexcept>

namespace KMLEngine {
    class DynamicLibrary final : public Disposable<DynamicLibrary>{
        friend Disposable<DynamicLibrary>;
    public:
        class Exception final : public std::runtime_error {
        public:
            explicit Exception(const std::string& message) noexcept : std::runtime_error(message) {}
        };
    private:
        void* m_handle = nullptr;
        std::filesystem::path m_path;

        [[nodiscard]] void* GetInternal(const std::string_view& name) const;

        void OnDisposing();
    public:
        void Create(const std::filesystem::path& path, const std::string_view& name);
        void Create(const std::filesystem::path& totalPath);

        template<typename T = void(*)()>
        [[nodiscard]] KML_FORCEINLINE typename AddOrKeepPointer<T>::Type Get(const std::string_view& name) const {
            return (typename AddOrKeepPointer<T>::Type)(GetInternal(name));
        }

        [[nodiscard]] KML_FORCEINLINE const std::filesystem::path& GetPath() const noexcept { return m_path; }
    };
}

#endif //KMLENGINE_COMMON_UTIL_LIBRARY_DYNAMICLIBRARY_HPP
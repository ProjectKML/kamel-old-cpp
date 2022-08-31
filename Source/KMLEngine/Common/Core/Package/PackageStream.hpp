//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: PackageStream.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_CORE_PACKAGE_PACKAGESTREAM_HPP
#define KMLENGINE_COMMON_CORE_PACKAGE_PACKAGESTREAM_HPP

#pragma once

#include "../../../Platform/Types.hpp"
#include "../../../Platform/Hints/ForceInline.hpp"
#include "../Memory/DefaultMemoryResource.hpp"
#include <vector>

namespace KMLEngine {
    class PackageLocation;
    class PackageStream final {
    private:
        std::pmr::vector<byte> m_buffer;
        usize m_offset = 0;

    public:
        enum class SeekMode {
            Begin = 0,
            Current = 1,
            End = 2
        };
    public:
        explicit PackageStream(const PackageLocation& location, std::pmr::memory_resource& memoryResource = DefaultMemoryResource::GetInstance());

        [[nodiscard]] usize Fread(void* buffer, usize size) noexcept;
        [[nodiscard]] i32 Fseek(usize size, SeekMode seekMode = SeekMode::Begin) noexcept;
        [[nodiscard]] KML_FORCEINLINE usize Ftell() noexcept { return m_offset; }

        [[nodiscard]] KML_FORCEINLINE usize GetSize() const noexcept { return m_buffer.size(); }
    };
}

#endif //KMLENGINE_COMMON_CORE_PACKAGE_PACKAGESTREAM_HPP
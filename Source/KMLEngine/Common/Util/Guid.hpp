//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Guid.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_GUID_HPP
#define KMLENGINE_COMMON_UTIL_GUID_HPP

#pragma once

#include "../../Platform/Types.hpp"
#include "../../Platform/Hints/ForceInline.hpp"
#include "HashCode.hpp"
#include <array>
#include <ostream>

namespace KMLEngine {
    struct Guid {
        union {
            std::array<u8, 16> U8 = {};
            std::array<u16, 8> U16;
            std::array<u32, 4> U32;
            std::array<u64, 2> U64;
        };

        Guid();

        friend std::ostream& operator <<(std::ostream& stream, const Guid& guid);
        [[nodiscard]] std::string ToString() const noexcept;

        [[nodiscard]] bool IsEmpty() const noexcept { return U64[0] == 0 && U64[1] == 0; }

        [[nodiscard]] KML_FORCEINLINE bool operator ==(const Guid& other) const noexcept { return U64[0] == other.U64[0] && U64[1] == other.U64[1]; }
        [[nodiscard]] KML_FORCEINLINE bool operator !=(const Guid& other) const noexcept { return U64[0] != other.U64[0] || U64[1] != other.U64[1]; }

        [[nodiscard]] static Guid NewGuid();
        [[nodiscard]] static Guid FromString(const std::string_view& str);
    };
}

namespace std {
    using namespace KMLEngine;

    template<>
    struct hash<Guid> {
        KML_FORCEINLINE usize operator()(const Guid& guid) const noexcept { return HashCode::Combine(guid.U64[0], guid.U64[1]); }
    };
}

#endif //KMLENGINE_COMMON_UTIL_GUID_HPP

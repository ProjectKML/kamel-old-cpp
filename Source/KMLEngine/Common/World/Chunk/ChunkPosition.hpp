//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ChunkPosition.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_WORLD_CHUNK_CHUNKPOSITION_HPP
#define KMLENGINE_COMMON_WORLD_CHUNK_CHUNKPOSITION_HPP

#pragma once

#include "../../../Platform/Types.hpp"
#include "../../../Platform/Hints/ForceInline.hpp"
#include "../../Util/HashCode.hpp"

namespace KMLEngine {
    struct ChunkPosition {
        i32 X, Y;

        explicit ChunkPosition(i32 x = 0, i32 y = 0) noexcept : X(x), Y(y) {}

        [[nodiscard]] KML_FORCEINLINE bool operator ==(const ChunkPosition& other) const noexcept  {
            return X == other.X && Y == other.Y;
        }

        [[nodiscard]] KML_FORCEINLINE bool operator !=(const ChunkPosition& other) const noexcept {
            return X != other.X || Y != other.Y;
        }
    };
}

namespace std {
    using namespace KMLEngine;

    template<>
    struct hash<ChunkPosition> {
        [[nodiscard]] KML_FORCEINLINE bool operator()(const ChunkPosition& position) const noexcept {
            return HashCode::Combine(position.X, position.Y);
        }
    };
}

#endif //KMLENGINE_COMMON_WORLD_CHUNK_CHUNKPOSITION_HPP
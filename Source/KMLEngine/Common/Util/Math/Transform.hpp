//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Transform.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_MATH_TRANSFORM_HPP
#define KMLENGINE_COMMON_UTIL_MATH_TRANSFORM_HPP

#pragma once

#include <glm/glm.hpp>

namespace KMLEngine {
    struct Transform {
        glm::vec3 Position;
        glm::quat Rotation;
        glm::vec3 Scale;

        explicit Transform(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                  const glm::quat rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f),
                  const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
                  Position(position), Rotation(rotation), Scale(scale) {}

        [[nodiscard]] KML_FORCEINLINE bool operator ==(const Transform& other) const noexcept {
            return Position == other.Position && Rotation == other.Rotation && Scale == other.Scale;
        }

        [[nodiscard]] KML_FORCEINLINE bool operator !=(const Transform& other) const noexcept {
            return Position != other.Position || Rotation != other.Rotation || Scale != other.Scale;
        }
    };
}

#endif //KMLENGINE_COMMON_UTIL_MATH_TRANSFORM_HPP
//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: MathHelper.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_MATH_MATHHELPER_HPP
#define KMLENGINE_COMMON_UTIL_MATH_MATHHELPER_HPP

#pragma once

#include "../../../Platform/Types.hpp"
#include "../../../Platform/Hints/ForceInline.hpp"
#include <glm/glm.hpp>

namespace KMLEngine::MathHelper {
    KML_FORCEINLINE glm::mat4 ReverseDepthProjectionMatrixLH(f32 fieldOfView, f32 aspectRatio, f32 nearPlane, f32 farPlane) noexcept {
        const auto tanHalfFovY = glm::tan(glm::radians(fieldOfView) / 2.0f);
        const auto farMinusNear = farPlane - nearPlane;
        
        glm::mat4 result(0.0f);
        result[0][0] = 1.0f / (aspectRatio * tanHalfFovY);
        result[1][1] = -1.0f / (tanHalfFovY);
        result[2][2] = farPlane / farMinusNear - 1.0f;
        result[2][3] = -1.0f;
        result[3][2] = (farPlane * nearPlane) / farMinusNear;

        return result;
    }

    KML_FORCEINLINE glm::vec3 DirectionFromRotationPYR(const glm::vec3& rotation) noexcept {
        const auto cosY = glm::cos(rotation.y);

        glm::vec3 v;
        v.x = glm::sin(rotation.x) * cosY;
        v.y = glm::sin(rotation.y);
        v.z = glm::cos(rotation.x) * cosY;
        return v; //TODO: check if roll is calculated correctly
    }
}

#endif //KMLENGINE_COMMON_UTIL_MATH_MATHHELPER_HPP

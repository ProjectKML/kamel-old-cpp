//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Camera.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_CAMERA_CAMERA_HPP
#define KMLENGINE_CLIENT_CAMERA_CAMERA_HPP

#pragma once

#include "../../Platform/Types.hpp"
#include "../../Platform/Hints/ForceInline.hpp"
#include <glm/glm.hpp>
#include <array>

namespace KMLEngine {
    struct TimerEventArgs;
    
    class Camera {
    public:
        static const f32 FIELD_OF_VIEW;
        static const f32 ASPECT_RATIO;
        static const f32 NEAR_PLANE;
        static const f32 FAR_PLANE;
    protected:
        glm::vec3 m_position = {};
        glm::vec3 m_rotation = {};

        f32 m_fieldOfView = FIELD_OF_VIEW; //degrees
        f32 m_aspectRatio = ASPECT_RATIO;
        f32 m_nearPlane = NEAR_PLANE;
        f32 m_farPlane = FAR_PLANE;
        
        glm::mat4 m_viewMatrix = {};
        glm::mat4 m_projectionMatrix = {};
        glm::mat4 m_viewProjectionMatrix = {};

        std::array<glm::vec4, 6> m_frustumPlanes = {};

        virtual void OnUpdate(const TimerEventArgs& timerEventArgs) = 0;
    public:
        Camera() = default;
        Camera(const glm::vec3& position,
            const glm::vec3& rotation,
            f32 fieldOfView = FIELD_OF_VIEW,
            f32 aspectRatio = ASPECT_RATIO,
            f32 nearPlane = NEAR_PLANE,
            f32 farPlane = FAR_PLANE) noexcept;

        virtual ~Camera() = default;

        void Update(const TimerEventArgs& timerEventArgs);
        
        virtual void RefreshViewMatrix() noexcept;
        virtual void RefreshProjectionMatrix() noexcept;
        
        //Getter
        [[nodiscard]] KML_FORCEINLINE const glm::vec3& GetPosition() const noexcept { return m_position; }
        [[nodiscard]] KML_FORCEINLINE const glm::vec3& GetRotation() const noexcept { return m_rotation; }

        [[nodiscard]] KML_FORCEINLINE f32 GetFieldOfView() const noexcept { return m_fieldOfView; }
        [[nodiscard]] KML_FORCEINLINE f32 GetAspectRatio() const noexcept { return m_aspectRatio; }
        [[nodiscard]] KML_FORCEINLINE f32 GetNearPlane() const noexcept { return m_nearPlane; }
        [[nodiscard]] KML_FORCEINLINE f32 GetFarPlane() const noexcept { return m_farPlane; }
        
        [[nodiscard]] KML_FORCEINLINE const glm::mat4& GetViewMatrix() const noexcept { return m_viewMatrix; }
        [[nodiscard]] KML_FORCEINLINE const glm::mat4& GetProjectionMatrix() const noexcept { return m_projectionMatrix; }
        [[nodiscard]] KML_FORCEINLINE const glm::mat4& GetViewProjectionMatrix() const noexcept { return m_viewProjectionMatrix; }

        [[nodiscard]] KML_FORCEINLINE const std::array<glm::vec4, 6>& GetFrustumPlanes() const noexcept { return m_frustumPlanes; }
    };
}

#endif //KMLENGINE_CLIENT_CAMERA_CAMERA_HPP
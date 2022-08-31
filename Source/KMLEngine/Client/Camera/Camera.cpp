//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Camera.cpp
//------------------------------------------------------------

#include "Camera.hpp"
#include "../../Common/Util/Math/MathHelper.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace KMLEngine {
    const f32 Camera::FIELD_OF_VIEW = 90.0f;
    const f32 Camera::ASPECT_RATIO = 16.0f / 9.0f;
    const f32 Camera::NEAR_PLANE = 0.1f;
    const f32 Camera::FAR_PLANE = 10000.0f;
    
    Camera::Camera(const glm::vec3& position, const glm::vec3& rotation, f32 fieldOfView, f32 aspectRatio,
        f32 nearPlane, f32 farPlane) noexcept : m_position(position), m_rotation(rotation), m_fieldOfView(fieldOfView), m_aspectRatio(aspectRatio), m_nearPlane(nearPlane), m_farPlane(farPlane) {
    }

    void Camera::Update(const TimerEventArgs& timerEventArgs) {
        OnUpdate(timerEventArgs);

        RefreshViewMatrix();
        RefreshProjectionMatrix();

        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void Camera::RefreshViewMatrix() noexcept {
        const auto direction = MathHelper::DirectionFromRotationPYR(m_rotation);
        const auto lookAt = m_position + direction;

        m_viewMatrix = glm::lookAt(m_position, lookAt, glm::vec3(0.0f, 1.f, 0.0f));
    }

    void Camera::RefreshProjectionMatrix() noexcept {
        m_projectionMatrix = MathHelper::ReverseDepthProjectionMatrixLH(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);
    }
}

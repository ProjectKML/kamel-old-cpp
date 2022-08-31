//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: FreeCamera.cpp
//------------------------------------------------------------

#include "FreeCamera.hpp"
#include "../Core/Input/Input.hpp"
#include "../../Common/Util/Time/TimerEventArgs.hpp"
#include "../Core/Input/Mouse.hpp"
#include "../Core/Window/Window.hpp"
#include "../Core/Window/Cursor.hpp"
#include <glm/gtc/constants.hpp>

namespace KMLEngine {
    static const f32 _S_SPEED = 12.5f;
    static const f32 _S_SENSITIVITY_X = 0.165F;
    static const f32 _S_SENSITIVITY_Y = 0.165F;
    
    void FreeCamera::OnUpdate(const TimerEventArgs& timerEventArgs) {
        Cursor::Disable();
        
        const auto sinPitch = glm::sin(m_rotation.x);
        const auto cosPitch = glm::cos(m_rotation.x);

        const auto deltaTime = static_cast<f32>(timerEventArgs.DeltaTime.GetSeconds());

        if(Input::IsKeyDown(EKeys::Key_W)) {
            m_position.x += sinPitch * _S_SPEED * deltaTime;
            m_position.z += cosPitch * _S_SPEED * deltaTime;
        }

        if(Input::IsKeyDown(EKeys::Key_A)) {
            m_position.x += cosPitch * _S_SPEED * deltaTime;
            m_position.z -= sinPitch * _S_SPEED * deltaTime;
        }

        if(Input::IsKeyDown(EKeys::Key_S)) {
            m_position.x -= sinPitch * _S_SPEED * deltaTime;
            m_position.z -= cosPitch * _S_SPEED * deltaTime;
        }

        if(Input::IsKeyDown(EKeys::Key_D)) {
            m_position.x -= cosPitch * _S_SPEED * deltaTime;
            m_position.z += sinPitch * _S_SPEED * deltaTime;
        }

        if(Input::IsKeyDown(EKeys::Key_SPACE)) {
            m_position.y += _S_SPEED * deltaTime;
        }

        if(Input::IsKeyDown(EKeys::Key_LSHIFT)) {
            m_position.y -= _S_SPEED * deltaTime;
        }

        const auto deltaPosition = Input::GetMousePosition() - Input::GetLastMousePosition();
        const auto movePosition = deltaPosition.Cast<f32>() * PointF32(_S_SENSITIVITY_X, _S_SENSITIVITY_Y) * 0.0073f;

        m_rotation.x += movePosition.X;
        if(m_rotation.x > glm::two_pi<f32>()) m_rotation.x = 0.0f;
        else if(m_rotation.x < 0.0f) m_rotation.x = glm::two_pi<f32>();

        m_rotation.y += movePosition.Y;
        if(m_rotation.y > glm::half_pi<f32>() - 0.15f) m_rotation.y = glm::half_pi<f32>() - 0.15f;
        else if(m_rotation.y < 0.15f - glm::half_pi<f32>()) m_rotation.y = 0.15f - glm::half_pi<f32>();
    }
}

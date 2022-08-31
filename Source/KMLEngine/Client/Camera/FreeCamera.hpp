//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: FreeCamera.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_CAMERA_FREECAMERA_HPP
#define KMLENGINE_CLIENT_CAMERA_FREECAMERA_HPP

#pragma once

#include "Camera.hpp"

namespace KMLEngine {
    class FreeCamera final : public Camera {
    private:
        void OnUpdate(const TimerEventArgs& timerEventArgs) final;
    };
}

#endif //KMLENGINE_CLIENT_CAMERA_FREECAMERA_HPP
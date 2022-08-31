//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: GeometryRenderer.cpp
//------------------------------------------------------------

#include "GeometryRenderer.hpp"

namespace KMLEngine {
    void GeometryRenderer::Render(const RenderFrameResources& currentFrame, Vulkan::CommandBuffer& commandBuffer, const TimerEventArgs& timerEventArgs) {
        RenderStaticGeometry(currentFrame, commandBuffer, timerEventArgs);
    }
}

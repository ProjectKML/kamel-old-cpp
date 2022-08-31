//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: GeometryRenderer.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_DEFERRED_GEOMETRY_GEOMETRYRENDERER_HPP
#define KMLENGINE_CLIENT_RENDERER_DEFERRED_GEOMETRY_GEOMETRYRENDERER_HPP

#pragma once

namespace KMLEngine {
    class RenderFrameResources;
    struct TimerEventArgs;

    namespace Vulkan {
        class CommandBuffer;
    }

    class GeometryRenderer {
    protected:
        virtual void RenderStaticGeometry(const RenderFrameResources& currentFrame, Vulkan::CommandBuffer& commandBuffer, const TimerEventArgs& timerEventArgs) = 0;
    public:
        void Render(const RenderFrameResources& currentFrame, Vulkan::CommandBuffer& commandBuffer, const TimerEventArgs& timerEventArgs);
        virtual ~GeometryRenderer() = default;
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_DEFERRED_GEOMETRY_GEOMETRYRENDERER_HPP
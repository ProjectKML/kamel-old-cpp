//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: GeometryRendererDefault.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_DEFERRED_GEOMETRY_GEOMETRYRENDERERDEFAULT_HPP
#define KMLENGINE_CLIENT_RENDERER_DEFERRED_GEOMETRY_GEOMETRYRENDERERDEFAULT_HPP

#pragma once

#include "GeometryRenderer.hpp"

namespace KMLEngine {
    class RenderContext;

    class GeometryRendererDefault final : public GeometryRenderer {
    private:
        void RenderStaticGeometry(const RenderFrameResources& currentFrame, Vulkan::CommandBuffer& commandBuffer, const TimerEventArgs& timerEventArgs) final;
    public:
        explicit GeometryRendererDefault(RenderContext& context);
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_DEFERRED_GEOMETRY_GEOMETRYRENDERERDEFAULT_HPP
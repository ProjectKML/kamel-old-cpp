//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: FullscreenTriangleRenderer.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_DEFERRED_FULLSCREENTRIANGLERENDERER_HPP
#define KMLENGINE_CLIENT_RENDERER_DEFERRED_FULLSCREENTRIANGLERENDERER_HPP

#pragma once

#include "../Vulkan/Pipeline/VulkanGraphicsPipeline.hpp"

namespace KMLEngine {
    class RenderContext;

    namespace Vulkan {
        class RenderPass;
        class CommandBuffer;
        class Framebuffer;
        class DescriptorSet;
    }

    class FullscreenTriangleRenderer final : public Disposable<FullscreenTriangleRenderer> {
        friend Disposable<FullscreenTriangleRenderer>;
    private:
        Vulkan::GraphicsPipeline m_pipeline;

        void OnDisposing();
    public:
        void Create(RenderContext& context, Vulkan::RenderPass& renderPass);

        void Render(Vulkan::CommandBuffer& commandBuffer, Vulkan::DescriptorSet& imageDescriptorSet);
        void Render(Vulkan::CommandBuffer& commandBuffer, Vulkan::Framebuffer& framebuffer, const Color4f& clearColor, Vulkan::DescriptorSet& imageDescriptorSet);
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_DEFERRED_FULLSCREENTRIANGLERENDERER_HPP
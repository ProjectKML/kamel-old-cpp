//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: FullscreenTriangleRenderer.cpp
//------------------------------------------------------------

#include "FullscreenTriangleRenderer.hpp"
#include "../Renderer.hpp"
#include "../Vulkan/Pipeline/VulkanShaderModule.hpp"
#include "../Vulkan/Descriptor/VulkanDescriptorSet.hpp"

namespace KMLEngine {
    void FullscreenTriangleRenderer::OnDisposing() {
        m_pipeline.Dispose();
    }

    void FullscreenTriangleRenderer::Create(RenderContext& context, Vulkan::RenderPass& renderPass) {
        Vulkan::ShaderModule vertexModule;
        vertexModule.Create(context.GetDevice(), PackageLocation("Resources", "fullscreen_triangle.vert.spv"));

        Vulkan::ShaderModule fragmentModule;
        fragmentModule.Create(context.GetDevice(), PackageLocation("Resources", "fullscreen_triangle.frag.spv"));

        Vulkan::GraphicsPipeline::Builder builder;
        builder.AddShaderStage(VK_SHADER_STAGE_VERTEX_BIT, vertexModule, "main")
            .AddShaderStage(VK_SHADER_STAGE_FRAGMENT_BIT, fragmentModule, "main")
            .SetInputAssemblyState(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST)
            .AddViewport(0.0f, 0.0f, 1.0f, 1.0f)
            .AddScissor(0, 0, 1, 1)
            .SetRasterizationState(VK_POLYGON_MODE_FILL, VK_CULL_MODE_NONE, VK_FRONT_FACE_CLOCKWISE)
            .SetMultisampleState(VK_SAMPLE_COUNT_1_BIT)
            .SetColorBlendState()
            .AddBlendAttachmentState()
            .AddDynamicState(VK_DYNAMIC_STATE_VIEWPORT)
            .AddDynamicState(VK_DYNAMIC_STATE_SCISSOR)
            .SetRenderPass(renderPass);

        m_pipeline.Create(context.GetDevice(), builder);

        fragmentModule.Dispose();
        vertexModule.Dispose();

        SetInitialized();
    }

    void FullscreenTriangleRenderer::Render(Vulkan::CommandBuffer& commandBuffer,
                                            Vulkan::DescriptorSet& imageDescriptorSet) {
        const auto size = Renderer::GetInstance().GetViewportManager().GetSize();

        const auto viewport = Vulkan::Utils::ViewportFromSize(size);
        const auto scissor = Vulkan::Utils::Rect2DFromSize(size);

        commandBuffer.SetViewport(0, 1, &viewport);
        commandBuffer.SetScissor(0, 1, &scissor);

        commandBuffer.BindPipeline(m_pipeline);
        commandBuffer.BindDescriptorSet(m_pipeline, imageDescriptorSet);
        commandBuffer.Draw(3, 1, 0, 0);
    }

    void FullscreenTriangleRenderer::Render(Vulkan::CommandBuffer& commandBuffer,
                                            Vulkan::Framebuffer& framebuffer,
                                            const Color4f& clearColor,
                                            Vulkan::DescriptorSet& imageDescriptorSet) {
        const auto clearValue = Vulkan::Utils::ClearValueFromColor(clearColor);

        commandBuffer.BeginRenderPass(framebuffer, 1, &clearValue, VK_SUBPASS_CONTENTS_INLINE);
        Render(commandBuffer, imageDescriptorSet);
        commandBuffer.EndRenderPass();
    }
}
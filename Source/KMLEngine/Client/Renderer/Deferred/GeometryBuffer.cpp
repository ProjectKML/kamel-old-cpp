//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: GeometryBuffer.cpp
//------------------------------------------------------------

#include "GeometryBuffer.hpp"
#include "../Renderer.hpp"
#include "../Common/Frame/RenderFrameCollection.hpp"
#include "../Common/Frame/RenderFrameResources.hpp"
#include "../Vulkan/Util/VulkanUtils.hpp"

namespace KMLEngine {
    //GeometryBuffer::FrameData
    void GeometryBuffer::Frame::OnDisposing() {
        m_signalSemaphore.Dispose();
        m_commandBuffer.Dispose();

        m_framebuffer.Dispose();

        m_depthImageView.Dispose();
        m_depthImage.Dispose();

        m_specularImageView.Dispose();
        m_specularImage.Dispose();

        m_normalImageView.Dispose();
        m_normalImage.Dispose();

        m_diffuseImageView.Dispose();
        m_diffuseImage.Dispose();
    }

    void GeometryBuffer::Frame::Create(RenderFrameResources& currentFrame, RenderContext& context, Vulkan::RenderPass& renderPass, u32 width, u32 height) {
        auto& device = context.GetDevice();
        
        m_diffuseImage.Create(device, VK_IMAGE_TYPE_2D, VK_FORMAT_R8G8B8A8_UNORM, width, height, 1, 1, 1, VK_SAMPLE_COUNT_1_BIT, VMA_MEMORY_USAGE_GPU_ONLY,
                              VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                              VK_IMAGE_LAYOUT_UNDEFINED);
        m_diffuseImageView.Create(device, m_diffuseImage, VK_IMAGE_VIEW_TYPE_2D, VK_FORMAT_R8G8B8A8_UNORM);

        m_normalImage.Create(device, VK_IMAGE_TYPE_2D, VK_FORMAT_R8G8B8A8_SNORM, width, height, 1, 1, 1, VK_SAMPLE_COUNT_1_BIT, VMA_MEMORY_USAGE_GPU_ONLY,
                             VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                             VK_IMAGE_LAYOUT_UNDEFINED);
        m_normalImageView.Create(device, m_normalImage, VK_IMAGE_VIEW_TYPE_2D, VK_FORMAT_R8G8B8A8_SNORM);

        m_specularImage.Create(device, VK_IMAGE_TYPE_2D, VK_FORMAT_R8G8B8A8_UNORM, width, height, 1, 1, 1, VK_SAMPLE_COUNT_1_BIT, VMA_MEMORY_USAGE_GPU_ONLY,
                               VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                               VK_IMAGE_LAYOUT_UNDEFINED);
        m_specularImageView.Create(device, m_specularImage, VK_IMAGE_VIEW_TYPE_2D, VK_FORMAT_R8G8B8A8_UNORM);

        m_depthImage.Create(device, VK_IMAGE_TYPE_2D, VK_FORMAT_D32_SFLOAT, width, height, 1, 1, 1, VK_SAMPLE_COUNT_1_BIT, VMA_MEMORY_USAGE_GPU_ONLY,
                            VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                            VK_IMAGE_LAYOUT_UNDEFINED);
        m_depthImageView.Create(device, m_depthImage, VK_IMAGE_VIEW_TYPE_2D, VK_FORMAT_D32_SFLOAT,
                                Vulkan::Utils::ComponentMapping(),
                                Vulkan::Utils::ImageSubresourceRange(VK_IMAGE_ASPECT_DEPTH_BIT));

        Vulkan::Framebuffer::Builder builder;
        builder.AddAttachment(m_diffuseImageView)
               .AddAttachment(m_normalImageView)
               .AddAttachment(m_specularImageView)
               .AddAttachment(m_depthImageView)
               .SetSize(width, height, 1)
               .SetRenderPass(renderPass);

        m_framebuffer.Create(device, builder);

        m_commandBuffer.AllocatePrimary(currentFrame.GetCommandPool());
        m_signalSemaphore.Create(device);

        SetInitialized();
    }

    //GeometryBuffer
    void GeometryBuffer::OnDisposing() {
        m_frameCollection.Destroy();
        m_renderPass.Dispose();
    }

    void GeometryBuffer::Create(RenderFrameManager& frameManager, RenderContext& context, u32 width, u32 height) {
        auto& device = context.GetDevice();
        
        Vulkan::RenderPass::SubpassBuilder subpassBuilder;
        subpassBuilder.AddColorAttachment(0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
        subpassBuilder.AddColorAttachment(1, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
        subpassBuilder.AddColorAttachment(2, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
        subpassBuilder.SetDepthStencilAttachment(3, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL).SetBindPoint(VK_PIPELINE_BIND_POINT_GRAPHICS);

        Vulkan::RenderPass::Builder builder;
        builder.AddAttachmentDescription(VK_FORMAT_R8G8B8A8_UNORM, VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE,
                                         VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        builder.AddAttachmentDescription(VK_FORMAT_R8G8B8A8_SNORM, VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE,
                                         VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        builder.AddAttachmentDescription(VK_FORMAT_R8G8B8A8_UNORM, VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE,
                                         VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        builder.AddAttachmentDescription(VK_FORMAT_D32_SFLOAT, VK_SAMPLE_COUNT_1_BIT, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE,
                                         VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        builder.AddSubpassDescription(subpassBuilder);

        m_renderPass.Create(device, builder);

        m_frameCollection.Create(frameManager, context, m_renderPass, width, height);

        SetInitialized();
    }

    void GeometryBuffer::Resize(RenderFrameManager& frameManager, RenderContext& context, u32 newWidth, u32 newHeight) {
        m_frameCollection.ForEach(frameManager, [&](RenderFrameResources& currentFrame, Frame& frame) {
            frame.Dispose();
            frame.Create(currentFrame, context, m_renderPass, newWidth, newHeight);
        });
    }
}

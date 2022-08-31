//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanCommandBuffer.cpp
//------------------------------------------------------------

#include "VulkanCommandBuffer.hpp"
#include "VulkanCommandPool.hpp"
#include "../Util/VulkanUtils.hpp"
#include "../Image/VulkanFramebuffer.hpp"
#include "../../RenderContext.hpp"

namespace KMLEngine::Vulkan {
    void CommandBuffer::OnDisposing() {
        vkFreeCommandBuffers(*m_device, *m_commandPool, 1, &m_handle);
        m_handle = VK_NULL_HANDLE;

        m_commandPool = nullptr;
        m_device = nullptr;
    }

    void CommandBuffer::Allocate(CommandPool& commandPool, VkCommandBufferLevel level) {
        m_device = &commandPool.GetDevice();
        m_commandPool = &commandPool;

        const auto commandBufferAllocateInfo = Utils::CommandBufferAllocateInfo(commandPool, level, 1);
        ThrowIfFailed(vkAllocateCommandBuffers(*m_device, &commandBufferAllocateInfo, &m_handle), "vkAllocateCommandBuffers");

        SetInitialized();
    }

    void CommandBuffer::BeginRenderPass(Framebuffer& framebuffer, u32 clearValueCount, const VkClearValue* pClearValues, VkSubpassContents contents) noexcept {
        KML_ASSERT(clearValueCount);
        KML_ASSERT(pClearValues);

        const auto renderPassBeginInfo = Utils::RenderPassBeginInfo(framebuffer.GetRenderPass(), framebuffer.GetHandle(),
                                                                    Utils::Offset2D(0, 0),
                                                                    Utils::Extent2D(framebuffer.GetWidth(), framebuffer.GetHeight()),
                                                                    clearValueCount,
                                                                    pClearValues);

        vkCmdBeginRenderPass(m_handle, &renderPassBeginInfo, contents);
    }

    void CommandBuffer::BeginDebugLabel(const char* name, const Color4f& color) noexcept {
        KML_ASSERT(name);

        if(RenderContext::GetInstance().GetVkInstance().AreValidationLayersEnabled()) {
            const auto debugUtilsLabel = Utils::DebugUtilsLabelEXT(name, color.R, color.G, color.B, color.A);

            vkCmdBeginDebugUtilsLabelEXT(m_handle, &debugUtilsLabel);
        }
    }

    void CommandBuffer::EndDebugLabel() {
        if(RenderContext::GetInstance().GetVkInstance().AreValidationLayersEnabled()) {
            vkCmdEndDebugUtilsLabelEXT(m_handle);
        }
    }
}

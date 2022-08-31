//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanRenderPass.cpp
//------------------------------------------------------------

#include "VulkanRenderPass.hpp"
#include "../VulkanDevice.hpp"

namespace KMLEngine::Vulkan {
    RenderPass::Builder& RenderPass::Builder::AddSubpassDescription(const SubpassBuilder& builder) noexcept {
        m_subpassDescriptions.push_back(Utils::SubpassDescription(builder.m_bindPoint,
            static_cast<u32>(builder.m_colorAttachments.size()),
            builder.m_colorAttachments.data(),
            builder.m_depthStencilAttachmentUsed ? &builder.m_depthStencilAttachment : nullptr,
            static_cast<u32>(builder.m_inputAttachments.size()),
            builder.m_inputAttachments.data(),
            builder.m_resolveAttachments.data(),
            static_cast<u32>(builder.m_preserveAttachments.size()),
            builder.m_preserveAttachments.data()));

        return *this;
    }

    void RenderPass::OnDisposing() {        
        vkDestroyRenderPass(m_device->GetHandle(), m_handle, GetAllocator());
        m_handle = VK_NULL_HANDLE;

        m_device = nullptr;
    }

    void RenderPass::Create(Device& device, const Builder& builder) {
        m_device = &device;

        const auto renderPassCreateInfo = Utils::RenderPassCreateInfo(static_cast<u32>(builder.m_attachmentDescriptions.size()),
                                                                            builder.m_attachmentDescriptions.data(),
                                                                            static_cast<u32>(builder.m_subpassDescriptions.size()),
                                                                            builder.m_subpassDescriptions.data(),
                                                                            static_cast<u32>(builder.m_subpassDependencies.size()),
                                                                            builder.m_subpassDependencies.data());

        ThrowIfFailed(vkCreateRenderPass(device.GetHandle(), &renderPassCreateInfo, GetAllocator(), &m_handle),
                              "vkCreateRenderPass");

        SetInitialized();
    }
}

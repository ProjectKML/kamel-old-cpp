//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanFramebuffer.cpp
//------------------------------------------------------------

#include "VulkanFramebuffer.hpp"
#include "../Util/VulkanUtils.hpp"
#include "../VulkanDevice.hpp"

namespace KMLEngine::Vulkan {
    void Framebuffer::OnDisposing() {
        vkDestroyFramebuffer(*m_device, m_handle, GetAllocator());
        m_handle = VK_NULL_HANDLE;

        m_layers = 0;
        m_size = {};

        m_renderPass = VK_NULL_HANDLE;
		
        m_device = nullptr;
    }
	
    void Framebuffer::Create(Device& device, const Builder& builder) {
        KML_ASSERT(builder.m_renderPass);
        KML_ASSERT(builder.m_width);
        KML_ASSERT(builder.m_height);
        KML_ASSERT(builder.m_layers);

        m_device = &device;

        m_renderPass = builder.m_renderPass;

        m_size = PointU32(builder.m_width, builder.m_height);
        m_layers = builder.m_layers;

        const auto framebufferCreateInfo = Utils::FramebufferCreateInfo(builder.m_renderPass, static_cast<u32>(builder.m_attachments.size()),
                                                                                    builder.m_attachments.data(), builder.m_width, builder.m_height, builder.m_layers);

        ThrowIfFailed(vkCreateFramebuffer(device.GetHandle(), &framebufferCreateInfo, Vulkan::GetAllocator(), &m_handle),
                            "vkCreateFramebuffer");
		
        SetInitialized();
    }
}
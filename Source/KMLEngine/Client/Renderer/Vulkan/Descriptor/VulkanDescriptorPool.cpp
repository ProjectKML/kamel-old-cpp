//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanDescriptorPool.cpp
//------------------------------------------------------------

#include "VulkanDescriptorPool.hpp"
#include "../VulkanDevice.hpp"

namespace KMLEngine {
    void Vulkan::DescriptorPool::OnDisposing() {
        vkDestroyDescriptorPool(*m_device, m_handle, GetAllocator());
        m_handle = VK_NULL_HANDLE;

        m_device = nullptr;
    }
	
    void Vulkan::DescriptorPool::Create(Device& device, const VkDescriptorPoolCreateInfo& descriptorPoolCreateInfo) {
        m_device = &device;
		
        ThrowIfFailed(vkCreateDescriptorPool(device.GetHandle(), &descriptorPoolCreateInfo, GetAllocator(), &m_handle),
                            "vkCreateDescriptorPool");
        SetInitialized();
    }
}

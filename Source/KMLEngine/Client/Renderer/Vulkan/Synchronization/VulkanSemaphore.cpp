//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanSemaphore.cpp
//------------------------------------------------------------

#include "VulkanSemaphore.hpp"
#include "../VulkanDevice.hpp"

namespace KMLEngine::Vulkan {
    void Semaphore::OnDisposing() {
        vkDestroySemaphore(*m_device, m_handle, GetAllocator());
        m_handle = VK_NULL_HANDLE;

        m_device = nullptr;
    }
	
    void Semaphore::Create(Device& device, const VkSemaphoreCreateInfo& semaphoreCreateInfo) {
        m_device = &device;
		
        ThrowIfFailed(vkCreateSemaphore(device, &semaphoreCreateInfo, GetAllocator(), &m_handle), "vkCreateSemaphore");

        SetInitialized();
    }
}

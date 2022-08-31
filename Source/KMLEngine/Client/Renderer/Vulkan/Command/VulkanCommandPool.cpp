//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanDescriptorPool.cpp
//------------------------------------------------------------

#include "VulkanCommandPool.hpp"
#include "../Util/VulkanUtils.hpp"
#include "../VulkanDevice.hpp"

namespace KMLEngine::Vulkan {
    void CommandPool::OnDisposing() {
        vkDestroyCommandPool(*m_device, m_handle, GetAllocator());
        m_handle = VK_NULL_HANDLE;

        m_device = nullptr;
    }

    void CommandPool::Create(Device& device, const VkCommandPoolCreateInfo& commandPoolCreateInfo) {
        m_device = &device;
		
        ThrowIfFailed(vkCreateCommandPool(device, &commandPoolCreateInfo, GetAllocator(), &m_handle), "vkCreateCommandPool");

        SetInitialized();
    }
	
    void CommandPool::Create(Device& device, Queue& queue, VkCommandPoolCreateFlags flags) {
        Create(device, Utils::CommandPoolCreateInfo(queue.GetFamilyIndex(), nullptr, flags));
    }
	
    void CommandPool::Reset(VkCommandPoolResetFlags commandPoolResetFlags) {
        ThrowIfFailed(vkResetCommandPool(*m_device, m_handle, commandPoolResetFlags),
                            "vkResetCommandPool");
    }
}

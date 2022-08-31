//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanFence.cpp
//------------------------------------------------------------

#include "VulkanFence.hpp"
#include "../VulkanDevice.hpp"

namespace KMLEngine::Vulkan {
    void Fence::OnDisposing() {
        vkDestroyFence(*m_device, m_handle, GetAllocator());
        m_handle = VK_NULL_HANDLE;

        m_device = nullptr;
    }
	
    void Fence::Create(Device& device, const VkFenceCreateInfo& fenceCreateInfo) {
        m_device = &device;
        
        ThrowIfFailed(vkCreateFence(device, &fenceCreateInfo, GetAllocator(), &m_handle), "vkCreateFence");
        SetInitialized();
    }
	
    void Fence::Reset() { ThrowIfFailed(vkResetFences(*m_device, 1, &m_handle), "vkResetFences"); }
    void Fence::WaitFor() { ThrowIfFailed(vkWaitForFences(*m_device, 1, &m_handle, true, std::numeric_limits<u64>::max()), "vkWaitForFences"); }
    VkResult Fence::GetStatus() const { return vkGetFenceStatus(*m_device, m_handle); }
}

//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanBuffer.cpp
//------------------------------------------------------------

#include "VulkanBuffer.hpp"
#include "../Util/VulkanUtils.hpp"
#include "../VulkanDevice.hpp"

namespace KMLEngine::Vulkan {
    void Buffer::OnDisposing() {
        vmaDestroyBuffer(m_device->GetAllocator(), m_handle, m_allocation);
        m_handle = VK_NULL_HANDLE;

        m_usage = 0;
        m_memoryUsage = VMA_MEMORY_USAGE_UNKNOWN;
        m_size = 0;

        m_allocationInfo = {};
        m_allocation = VK_NULL_HANDLE;

        m_device = nullptr;
    }
	
    void* Buffer::MapInternal() {
        void* data;
        ThrowIfFailed(vmaMapMemory(m_device->GetAllocator(), m_allocation, &data), "vmaMapMemory");
        return data;
    }
	
    void Buffer::Create(Device& device, usize size, VmaMemoryUsage memoryUsage, VkBufferUsageFlags usage) {
        KML_ASSERT(size);
		
        m_device = &device;
        m_size = size;
        m_memoryUsage = memoryUsage;
        m_usage = usage;

        const auto bufferCreateInfo = Utils::BufferCreateInfo(size, usage);
        const auto allocationCreateInfo = Utils::AllocationCreateInfo(memoryUsage);

        ThrowIfFailed(vmaCreateBuffer(device.GetAllocator(), &bufferCreateInfo, &allocationCreateInfo, &m_handle, &m_allocation, &m_allocationInfo),
                            "vmaCreateBuffer");

        SetInitialized();
    }
	
    void Buffer::Unmap() noexcept { vmaUnmapMemory(m_device->GetAllocator(), m_allocation); }
}
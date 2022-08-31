//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanBuffer.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_BUFFER_VULKANBUFFER_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_BUFFER_VULKANBUFFER_HPP

#pragma once

#include "../Util/VulkanObject.hpp"

namespace KMLEngine::Vulkan {
    class Buffer final : public DeviceObject<VkBuffer, VK_OBJECT_TYPE_BUFFER>, public Disposable<Buffer> {
        friend Disposable<Buffer>;
    private:
        VmaAllocation m_allocation = VK_NULL_HANDLE;
        VmaAllocationInfo m_allocationInfo = {};

        usize m_size = 0;
        VmaMemoryUsage m_memoryUsage = VMA_MEMORY_USAGE_UNKNOWN;
        VkBufferUsageFlags m_usage = 0;
		
        void* MapInternal();
		
        void OnDisposing();
    public:
        void Create(Device& device, usize size, VmaMemoryUsage memoryUsage, VkBufferUsageFlags usage);

        template<typename T = void>
        [[nodiscard]] KML_FORCEINLINE T* Map() { return static_cast<T*>(MapInternal()); }

        void Unmap() noexcept;

        [[nodiscard]] KML_FORCEINLINE usize GetSize() const noexcept { return m_size; }
        [[nodiscard]] KML_FORCEINLINE VmaMemoryUsage GetMemoryUsage() const noexcept { return m_memoryUsage; }
        [[nodiscard]] KML_FORCEINLINE VkBufferUsageFlags GetUsage() const noexcept { return m_usage; }
		
        [[nodiscard]] KML_FORCEINLINE VmaAllocation& GetAllocation() noexcept {
            KML_ASSERT(m_allocation);
            return m_allocation;
        }
		
        [[nodiscard]] KML_FORCEINLINE const VmaAllocation& GetAllocation() const noexcept {
            KML_ASSERT(m_allocation);
            return m_allocation;
        }

        [[nodiscard]] KML_FORCEINLINE const VmaAllocationInfo& GetAllocationInfo() const noexcept { return m_allocationInfo; }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_BUFFER_VULKANBUFFER_HPP
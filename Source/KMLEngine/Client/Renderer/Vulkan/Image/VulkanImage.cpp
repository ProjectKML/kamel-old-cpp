//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanImage.cpp
//------------------------------------------------------------

#include "VulkanImage.hpp"
#include "../Util/VulkanUtils.hpp"
#include "../VulkanDevice.hpp"

namespace KMLEngine::Vulkan {
	void Image::OnDisposing() {
		vmaDestroyImage(m_device->GetAllocator(), m_handle, m_allocation);
		m_handle = VK_NULL_HANDLE;

		m_usage = 0;
		m_memoryUsage = VMA_MEMORY_USAGE_UNKNOWN;
		m_samples = VK_SAMPLE_COUNT_1_BIT;
		m_arrayLayers = 0;
		m_mipLevels = 0;
		m_depth = 0;
		m_height = 0;
		m_width = 0;
		m_format = VK_FORMAT_UNDEFINED;
		m_imageType = VK_IMAGE_TYPE_1D;

		m_allocationInfo = {};
		m_allocation = VK_NULL_HANDLE;

		m_device = nullptr;
	}

	void* Image::MapInternal() {
		void* data;
		ThrowIfFailed(vmaMapMemory(m_device->GetAllocator(), m_allocation, &data), "vmaMapMemory");
		return data;
	}

	void Image::Create(Device& device, VkImageType imageType, VkFormat format, u32 width, u32 height, u32 depth, u32 mipLevels, u32 arrayLayers,
						VkSampleCountFlagBits samples, VmaMemoryUsage memoryUsage, VmaAllocationCreateFlags allocationFlags, VkImageUsageFlags usage,
						VkImageLayout initialLayout, VkImageTiling tiling, VkSharingMode sharingMode, u32 queueFamilyIndexCount, const u32* queueFamilyIndices,
						const void* next, VkImageCreateFlags flags) {
		KML_ASSERT(width);
		KML_ASSERT(height);
		KML_ASSERT(depth);

		m_device = &device;

		m_imageType = imageType;
		m_format = format;
		m_width = width;
		m_height = height;
		m_depth = depth;
		m_mipLevels = mipLevels;
		m_arrayLayers = arrayLayers;
		m_samples = samples;
		m_memoryUsage = memoryUsage;
		m_usage = usage;

		const auto imageCreateInfo = Utils::ImageCreateInfo(imageType, format, Utils::Extent3D(width, height, depth), mipLevels, arrayLayers,
		                                                    samples, usage, initialLayout, tiling, sharingMode, queueFamilyIndexCount,
		                                                    queueFamilyIndices, next, flags);
		const auto allocationCreateInfo = Utils::AllocationCreateInfo(memoryUsage);

		ThrowIfFailed(vmaCreateImage(device.GetAllocator(), &imageCreateInfo, &allocationCreateInfo, &m_handle, &m_allocation, &m_allocationInfo),
		                      "vmaCreateImage");

		SetInitialized();
	}

	void Image::Unmap() noexcept { vmaUnmapMemory(m_device->GetAllocator(), m_allocation); }
}

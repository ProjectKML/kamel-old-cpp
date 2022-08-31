//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanImage.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_IMAGE_VULKANIMAGE_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_IMAGE_VULKANIMAGE_HPP

#pragma once

#include "../Util/VulkanObject.hpp"

namespace KMLEngine::Vulkan {
	class Image final : public DeviceObject<VkImage, VK_OBJECT_TYPE_IMAGE>, public Disposable<Image> {
		friend Disposable<Image>;
	private:
		VmaAllocation m_allocation = VK_NULL_HANDLE;
		VmaAllocationInfo m_allocationInfo = {};

		VkImageType m_imageType = VK_IMAGE_TYPE_1D;
		VkFormat m_format = VK_FORMAT_UNDEFINED;
		u32 m_width = 0;
		u32 m_height = 0;
		u32 m_depth = 0;
		u32 m_mipLevels = 0;
		u32 m_arrayLayers = 0;
		VkSampleCountFlagBits m_samples = VK_SAMPLE_COUNT_1_BIT;
		VmaMemoryUsage m_memoryUsage = VMA_MEMORY_USAGE_UNKNOWN;
		VkImageUsageFlags m_usage = 0;

		void* MapInternal();
		
		void OnDisposing();
	public:
		void Create(Device& device, VkImageType imageType, VkFormat format, u32 width, u32 height, u32 depth,
			u32 mipLevels, u32 arrayLayers, VkSampleCountFlagBits samples, VmaMemoryUsage memoryUsage,
			VmaAllocationCreateFlags allocationFlags, VkImageUsageFlags usage, VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL, VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE,
			u32 queueFamilyIndexCount = 0, const u32* queueFamilyIndices = nullptr, const void* next = nullptr, VkImageCreateFlags flags = 0);

		template<typename T = void>
		[[nodiscard]] KML_FORCEINLINE T* Map() { return static_cast<T*>(MapInternal()); }

		void Unmap() noexcept;

		[[nodiscard]] KML_FORCEINLINE VkImageType GetImageType() const noexcept { return m_imageType; }
		[[nodiscard]] KML_FORCEINLINE VkFormat GetFormat() const noexcept { return m_format; }
		[[nodiscard]] KML_FORCEINLINE u32 GetWidth() const noexcept { return m_width; }
		[[nodiscard]] KML_FORCEINLINE u32 GetHeight() const noexcept { return m_height; }
		[[nodiscard]] KML_FORCEINLINE u32 GetDepth() const noexcept { return m_depth; }
		[[nodiscard]] KML_FORCEINLINE u32 GetMipLevels() const noexcept { return m_mipLevels; }
		[[nodiscard]] KML_FORCEINLINE u32 GetArrayLayers() const noexcept { return m_arrayLayers; }
		[[nodiscard]] KML_FORCEINLINE VkSampleCountFlagBits GetSamples() const noexcept { return m_samples; }
		[[nodiscard]] KML_FORCEINLINE VmaMemoryUsage GetMemoryUsage() const noexcept { return m_memoryUsage; }
		[[nodiscard]] KML_FORCEINLINE VkImageUsageFlags GetUsage() const noexcept { return m_usage; }

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

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_IMAGE_VULKANIMAGE_HPP
//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanDevice.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANDEVICE_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANDEVICE_HPP

#pragma once

#include "VulkanQueue.hpp"
#include "Descriptor/VulkanDescriptorPool.hpp"
#include <vector>

namespace KMLEngine::Vulkan {
	class Instance;
	class PhysicalDevice;
	class DeviceResources;
	class Device final : public InstancePhysicalDeviceObject<VkDevice, VK_OBJECT_TYPE_DEVICE>, public Disposable<Device> {
		friend Disposable<Device>;
	private:
		VmaAllocator m_allocator = VK_NULL_HANDLE;
		DescriptorPool m_descriptorPool;
		DeviceResources* m_resources = nullptr;

		Queue m_directQueue, m_dedicatedComputeQueue, m_dedicatedTransferQueue;
		
		std::vector<const char*> m_enabledExtensions;

		void CreateMemoryAllocator();
		void CreateDescriptorPool();
		void CreateQueues(std::vector<VkDeviceQueueCreateInfo>& deviceQueueCreateInfos);
		void GetQueues();

		void EnsureFeaturesSupported();
		void EnableVulkan12Extensions();
		
		void OnDisposing();
	public:
		void Initialize(Instance& instance, PhysicalDevice& physicalDevice);
		void Create(const VkPhysicalDeviceFeatures2& enabledFeatures);

		KML_FORCEINLINE void WaitIdle() { ThrowIfFailed(vkDeviceWaitIdle(m_handle), "vkDeviceWaitIdle"); }

		bool TryAddExtension(const char* name) noexcept;
		void AddExtension(const char* name);
		bool IsExtensionEnabled(const char* name) const noexcept;

		void PrintProperties();

		[[nodiscard]] KML_FORCEINLINE VmaAllocator& GetAllocator() noexcept {
			KML_ASSERT(m_allocator);
			return m_allocator;
		}

		[[nodiscard]] KML_FORCEINLINE const VmaAllocator& GetAllocator() const noexcept {
			KML_ASSERT(m_allocator);
			return m_allocator;
		}

		[[nodiscard]] KML_FORCEINLINE DescriptorPool& GetDescriptorPool() noexcept { return m_descriptorPool; }
		[[nodiscard]] KML_FORCEINLINE const DescriptorPool& GetDescriptorPool() const noexcept { return m_descriptorPool; }
		
		[[nodiscard]] KML_FORCEINLINE DeviceResources& GetResources() noexcept {
			KML_ASSERT(m_resources);
			return *m_resources;
		}

		[[nodiscard]] KML_FORCEINLINE const DeviceResources& GetResources() const noexcept {
			KML_ASSERT(m_resources);
			return *m_resources;
		}
		
		[[nodiscard]] KML_FORCEINLINE Queue& GetDirectQueue() noexcept { return m_directQueue; }
		[[nodiscard]] KML_FORCEINLINE const Queue& GetDirectQueue() const noexcept { return m_directQueue; }

		[[nodiscard]] KML_FORCEINLINE Queue& GetDedicateComputeQueue() noexcept { return m_dedicatedComputeQueue; }
		[[nodiscard]] KML_FORCEINLINE const Queue& GetDedicateComputeQueue() const noexcept { return m_dedicatedComputeQueue; }

		[[nodiscard]] KML_FORCEINLINE Queue& GetDedicatedTransferQueue() noexcept { return m_dedicatedTransferQueue; }
		[[nodiscard]] KML_FORCEINLINE const Queue& GetDedicatedTransferQueue() const noexcept { return m_dedicatedTransferQueue; }
		
		[[nodiscard]] KML_FORCEINLINE const std::vector<const char*>& GetEnabledExtensions() const noexcept { return m_enabledExtensions; }
	};
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANDEVICE_HPP
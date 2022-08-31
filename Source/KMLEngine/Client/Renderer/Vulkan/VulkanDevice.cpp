//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanDevice.cpp
//------------------------------------------------------------

#include "VulkanDevice.hpp"
#include "VulkanInstance.hpp"
#include "VulkanPhysicalDevice.hpp"
#include "Util/VulkanUtils.hpp"
#include "VulkanDeviceResources.hpp"
#include "../../../Common/Util/String/CString.hpp"
#include <spdlog/spdlog.h>

namespace KMLEngine::Vulkan {
	void Device::OnDisposing() {
		m_resources->Dispose();
		delete m_resources;

		m_descriptorPool.Dispose();

		vmaDestroyAllocator(m_allocator);
		m_allocator = VK_NULL_HANDLE;
		
		m_dedicatedTransferQueue.Dispose();
		m_dedicatedComputeQueue.Dispose();
		m_directQueue.Dispose();

		vkDestroyDevice(m_handle, Vulkan::GetAllocator());
		m_handle = VK_NULL_HANDLE;
		
		m_physicalDevice = VK_NULL_HANDLE;
		m_instance = VK_NULL_HANDLE;
	}

	void Device::CreateMemoryAllocator() {
		const auto allocatorCreateInfo = Utils::AllocatorCreateInfo(m_physicalDevice->GetHandle(), m_handle, *m_instance,
																VK_API_VERSION_1_1, Vulkan::GetAllocator());

		ThrowIfFailed(vmaCreateAllocator(&allocatorCreateInfo, &m_allocator), "vmaCreateAllocator");
	}

	void Device::CreateDescriptorPool() {
		DescriptorPool::Builder builder;
		builder.AddPoolSize(VK_DESCRIPTOR_TYPE_SAMPLER, 32);
		builder.AddPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 32);
		builder.AddPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 32);
		builder.AddPoolSize(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 32); //TODO:

		m_descriptorPool.Create(*this, builder);
	}
	
	void Device::CreateQueues(std::vector<VkDeviceQueueCreateInfo>& deviceQueueCreateInfos) {
		static const f32 singlePriority = 1.0f;

		const auto directQueueFamilyIndex = m_physicalDevice->GetDirectQueueFamilyIndex();
		const auto dedicatedComputeQueueFamilyIndex = m_physicalDevice->GetDedicatedComputeQueueFamilyIndex();
		const auto dedicatedTransferQueueFamilyIndex = m_physicalDevice->GetDedicatedTransferQueueFamilyIndex();

		const auto graphicsQueueCreateInfo = Utils::DeviceQueueCreateInfo(directQueueFamilyIndex, 1, &singlePriority);
		deviceQueueCreateInfos.push_back(graphicsQueueCreateInfo);

		if(dedicatedComputeQueueFamilyIndex != directQueueFamilyIndex) {
			const auto computeQueueCreateInfo = Utils::DeviceQueueCreateInfo(dedicatedComputeQueueFamilyIndex, 1, &singlePriority);
			deviceQueueCreateInfos.push_back(computeQueueCreateInfo);
		}
		if(dedicatedTransferQueueFamilyIndex != dedicatedComputeQueueFamilyIndex && dedicatedTransferQueueFamilyIndex != directQueueFamilyIndex) {
			const auto transferQueueCreateInfo = Utils::DeviceQueueCreateInfo(dedicatedTransferQueueFamilyIndex, 1, &singlePriority);
			deviceQueueCreateInfos.push_back(transferQueueCreateInfo);
		}
	}

	void Device::GetQueues() {
		VkQueue directQueue, dedicatedComputeQueue, dedicatedTransferQueue;

		const auto directQueueFamilyIndex = m_physicalDevice->GetDirectQueueFamilyIndex();
		const auto dedicatedComputeQueueFamilyIndex = m_physicalDevice->GetDedicatedComputeQueueFamilyIndex();
		const auto dedicatedTransferQueueFamilyIndex = m_physicalDevice->GetDedicatedTransferQueueFamilyIndex();

		auto deviceQueueInfo = Utils::DeviceQueueInfo2(directQueueFamilyIndex, 0);
		vkGetDeviceQueue2(m_handle, &deviceQueueInfo, &directQueue);

		deviceQueueInfo.queueFamilyIndex = dedicatedComputeQueueFamilyIndex;
		vkGetDeviceQueue2(m_handle, &deviceQueueInfo, &dedicatedComputeQueue);

		deviceQueueInfo.queueFamilyIndex = dedicatedTransferQueueFamilyIndex;
		vkGetDeviceQueue2(m_handle, &deviceQueueInfo, &dedicatedTransferQueue);

		m_directQueue.Create(*this, directQueue, directQueueFamilyIndex);
		m_dedicatedComputeQueue.Create(*this, dedicatedComputeQueue, dedicatedComputeQueueFamilyIndex);
		m_dedicatedTransferQueue.Create(*this, dedicatedTransferQueue, dedicatedTransferQueueFamilyIndex);
	}

	void Device::EnsureFeaturesSupported() {
		if(!m_physicalDevice->IsVulkan11Supported()) throw Exception(fmt::format("Vulkan {}.{} not supported by device", 1, 1));
		if(!m_physicalDevice->IsVulkan12Supported()) {
			spdlog::warn("Vulkan {}.{} not supported by device", 1, 2);
			EnableVulkan12Extensions();
		}
	}

	void Device::EnableVulkan12Extensions() {
		AddExtension(VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME);
	}

	void Device::Initialize(Instance& instance, PhysicalDevice& physicalDevice) {
		m_instance = &instance;
		m_physicalDevice = &physicalDevice;
	}

	void Device::Create(const VkPhysicalDeviceFeatures2& enabledFeatures) {
		std::vector<VkDeviceQueueCreateInfo> deviceQueueCreateInfos;

		CreateQueues(deviceQueueCreateInfos);

		TryAddExtension("VK_KHR_portability_subset");

		EnsureFeaturesSupported();

		const auto deviceCreateInfo = Utils::DeviceCreateInfo(static_cast<u32>(deviceQueueCreateInfos.size()),
		                                                      deviceQueueCreateInfos.data(), 0, nullptr,
		                                                      static_cast<u32>(m_enabledExtensions.size()),
		                                                      m_enabledExtensions.data(), nullptr, &enabledFeatures);

		ThrowIfFailed(vkCreateDevice(*m_physicalDevice, &deviceCreateInfo, Vulkan::GetAllocator(), &m_handle), "vkCreateDevice");
		Loader::LoadDevice(m_handle);

		GetQueues();

		CreateMemoryAllocator();
		CreateDescriptorPool();

		m_resources = new DeviceResources;
		m_resources->Create(*this);

		SetInitialized();
	}

	bool Device::TryAddExtension(const char* name) noexcept {
		KML_ASSERT(name);

		if(m_physicalDevice->IsExtensionSupported(name)) {
			m_enabledExtensions.push_back(name);
			return true;
		}

		return false;
	}

	void Device::AddExtension(const char* name) {
		KML_ASSERT(name);

		if(!TryAddExtension(name)) throw Exception(fmt::format("Extension not supported: {}", name));
	}

	bool Device::IsExtensionEnabled(const char* name) const noexcept {
		KML_ASSERT(name);

		for(const auto* extension : m_enabledExtensions) {
			if(CString::AreStringsEqual(extension, name)) return true;
		}
		return false;
	}

	void Device::PrintProperties() {
		spdlog::info("===== VULKAN DEVICE =====");
		spdlog::info("Supported device extensions:");

		for(auto& supportedExtensions = m_physicalDevice->GetSupportedExtensions(); const auto& extension : supportedExtensions) {
			if(IsExtensionEnabled(extension.extensionName)) spdlog::info(reinterpret_cast<const char*>(u8"\t{} ✅"), extension.extensionName);
			else spdlog::info("\t{}", extension.extensionName);
		}
	}
}

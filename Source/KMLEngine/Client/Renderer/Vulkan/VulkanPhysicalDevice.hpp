//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanPhysicalDevice.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANPHYSICALDEVICE_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANPHYSICALDEVICE_HPP

#pragma once

#include "Util/VulkanObject.hpp"
#include "Util/VulkanStructureList.hpp"
#include <vector>

namespace KMLEngine::Vulkan {
	class Surface;
	class PhysicalDevice final : public Object<VkPhysicalDevice, VK_OBJECT_TYPE_PHYSICAL_DEVICE>, public Disposable<PhysicalDevice> {
		friend Disposable<PhysicalDevice>;
	private:
		//Properties --------------------------------------------------------------------------------------------------------------
		StructureList m_propertiesList;
		VkPhysicalDeviceProperties2 m_properties = {};
		VkPhysicalDeviceVulkan11Properties m_properties11 = {};
		VkPhysicalDeviceVulkan12Properties m_properties12 = {};
		
		VkPhysicalDeviceDescriptorIndexingProperties m_descriptorIndexingProperties = {};

		VkPhysicalDeviceMeshShaderPropertiesNV m_meshShaderProperties = {};

		//Memory Properties -------------------------------------------------------------------------------------------------------
		StructureList m_memoryPropertiesList;
		VkPhysicalDeviceMemoryProperties2 m_memoryProperties = {};

		//Queue family properties -------------------------------------------------------------------------------------------------
		std::vector<StructureList> m_queueFamilyPropertiesLists;
		std::vector<VkQueueFamilyProperties2> m_queueFamilyProperties;

		//Supported features ------------------------------------------------------------------------------------------------------
		StructureList m_supportedFeaturesList;
		VkPhysicalDeviceFeatures2 m_supportedFeatures = {};
		VkPhysicalDeviceVulkan11Features m_supportedFeatures11 = {};
		VkPhysicalDeviceVulkan12Features m_supportedFeatures12 = {};

		VkPhysicalDeviceDescriptorIndexingFeatures m_supportedDescriptorIndexingFeatures = {};

		VkPhysicalDeviceMeshShaderFeaturesNV m_supportedMeshShaderFeatures = {};

		//Queue family indices ----------------------------------------------------------------------------------------------------
		u32 m_directQueueFamilyIndex = 0, m_dedicatedComputeQueueFamilyIndex = 0, m_dedicatedTransferQueueFamilyIndex = 0;

		//Extensions --------------------------------------------------------------------------------------------------------------
		std::vector<VkExtensionProperties> m_supportedExtensions;

		bool m_hasDedicatedMemory = false;

		void FindProperties();
		void FindMemoryProperties();
		void FindQueueFamilyProperties();
		void FindSupportedFeatures();
		void FindHasDedicatedMemory();

		u32 FindDirectQueueFamilyIndex(Surface& surface) const;
		u32 FindDedicatedComputeQueueFamilyIndex() const;
		u32 FindDedicatedTransferQueueFamilyIndex() const;

		void FindSupportedExtensions();

		void OnDisposing();
	public:
		void Create(VkPhysicalDevice physicalDevice, Surface& surface);

		//Getter
		bool IsVulkan11Supported() const noexcept;
		bool IsVulkan12Supported() const noexcept;
		bool IsExtensionSupported(const char* name) const noexcept;
		
		//Properties -----------------------------------------------------------------------------------------------------------------------------------------------
		[[nodiscard]] KML_FORCEINLINE const VkPhysicalDeviceProperties2& GetProperties() const noexcept { return m_properties; }
		[[nodiscard]] KML_FORCEINLINE const VkPhysicalDeviceVulkan11Properties& GetProperties11() const noexcept { return m_properties11; }
		[[nodiscard]] KML_FORCEINLINE const VkPhysicalDeviceVulkan12Properties& GetProperties12() const noexcept { return m_properties12; }

		[[nodiscard]] KML_FORCEINLINE const VkPhysicalDeviceDescriptorIndexingProperties& GetDescriptorIndexingProperties() const noexcept { return m_descriptorIndexingProperties; }

		[[nodiscard]] KML_FORCEINLINE const VkPhysicalDeviceMeshShaderPropertiesNV& GetMeshShaderProperties() const noexcept { return m_meshShaderProperties; }

		//Memory Properties ----------------------------------------------------------------------------------------------------------------------------------------
		[[nodiscard]] KML_FORCEINLINE const VkPhysicalDeviceMemoryProperties2& GetMemoryProperties() const noexcept { return m_memoryProperties; }

		//Queue family properties ----------------------------------------------------------------------------------------------------------------------------------
		[[nodiscard]] KML_FORCEINLINE const std::vector<VkQueueFamilyProperties2>& GetQueueFamilyProperties() const noexcept { return m_queueFamilyProperties; }

		//Supported features ---------------------------------------------------------------------------------------------------------------------------------------
		[[nodiscard]] KML_FORCEINLINE const VkPhysicalDeviceFeatures2& GetSupportedFeatures() const noexcept { return m_supportedFeatures; }
		[[nodiscard]] KML_FORCEINLINE const VkPhysicalDeviceVulkan11Features& GetSupportedFeatures11() const noexcept { return m_supportedFeatures11; }
		[[nodiscard]] KML_FORCEINLINE const VkPhysicalDeviceVulkan12Features& GetSupportedFeatures12() const noexcept { return m_supportedFeatures12; }

		[[nodiscard]] KML_FORCEINLINE const VkPhysicalDeviceDescriptorIndexingFeatures& GetSupportedDescriptorIndexingFeatures() const noexcept { return m_supportedDescriptorIndexingFeatures; }

		[[nodiscard]] KML_FORCEINLINE const VkPhysicalDeviceMeshShaderFeaturesNV& GetSupportedMeshShaderFeatures() const noexcept { return m_supportedMeshShaderFeatures; }

		//Supported extensions ----------------------------------------------------------------------------------------------------------------------------------------
		[[nodiscard]] KML_FORCEINLINE const std::vector<VkExtensionProperties>& GetSupportedExtensions() const noexcept { return m_supportedExtensions; }

		[[nodiscard]] KML_FORCEINLINE u32 GetDirectQueueFamilyIndex() const noexcept { return m_directQueueFamilyIndex; }
		[[nodiscard]] KML_FORCEINLINE u32 GetDedicatedComputeQueueFamilyIndex() const noexcept { return m_dedicatedComputeQueueFamilyIndex; }
		[[nodiscard]] KML_FORCEINLINE u32 GetDedicatedTransferQueueFamilyIndex() const noexcept { return m_dedicatedTransferQueueFamilyIndex; }

		[[nodiscard]] KML_FORCEINLINE bool HasDedicatedMemory() const noexcept { return m_hasDedicatedMemory; }
	};
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANPHYSICALDEVICE_HPP
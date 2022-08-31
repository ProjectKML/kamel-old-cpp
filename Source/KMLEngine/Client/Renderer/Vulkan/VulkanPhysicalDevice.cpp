//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanPhysicalDevice.cpp
//------------------------------------------------------------

#include "VulkanPhysicalDevice.hpp"
#include "VulkanSurface.hpp"
#include "../../../Common/Util/String/CString.hpp"
#include <spdlog/spdlog.h>

namespace KMLEngine::Vulkan {
	void PhysicalDevice::OnDisposing() {
		m_supportedExtensions.clear();
		
		m_dedicatedTransferQueueFamilyIndex = 0;
		m_dedicatedComputeQueueFamilyIndex = 0;
		m_directQueueFamilyIndex = 0;

		//Supported features ------------------------
		m_supportedMeshShaderFeatures = {};

		m_supportedDescriptorIndexingFeatures = {};

		m_supportedFeatures12 = {};
		m_supportedFeatures11 = {};
		m_supportedFeatures = {};
		m_supportedFeaturesList.Clear();
		
		//Queue family properties --------------------
		m_queueFamilyProperties.clear();
		m_queueFamilyPropertiesLists.clear();

		//Supported features -------------------------
		m_memoryProperties = {};
		m_memoryPropertiesList.Clear();

		//Properties ---------------------------------
		m_meshShaderProperties = {};

		m_descriptorIndexingProperties = {};

		m_properties12 = {};
		m_properties11 = {};
		m_properties = {};
		m_propertiesList.Clear();
	}

	void PhysicalDevice::FindProperties() {
		//Set structure types
		m_properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
		m_properties11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES;
		m_properties12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES;
		
		m_descriptorIndexingProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_PROPERTIES;

		m_meshShaderProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_NV;

		//Add structures
		m_propertiesList.Add(&m_properties);
		m_propertiesList.Add(&m_properties11);
		if(IsVulkan12Supported()) m_propertiesList.Add(&m_properties12);
		else {
			if(IsExtensionSupported(VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME)) m_propertiesList.Add(&m_descriptorIndexingProperties);
		}

		if(IsExtensionSupported(VK_NV_MESH_SHADER_EXTENSION_NAME)) m_propertiesList.Add(&m_meshShaderProperties);
		
		vkGetPhysicalDeviceProperties2(m_handle, &m_properties);
	}
	
	void PhysicalDevice::FindMemoryProperties() {
		//Set structure types
		m_memoryProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2;

		//Add structures
		m_memoryPropertiesList.Add(&m_memoryProperties);

		vkGetPhysicalDeviceMemoryProperties2(m_handle, &m_memoryProperties);
	}
	
	void PhysicalDevice::FindQueueFamilyProperties() {
		u32 numQueueFamilyProperties;
		
		vkGetPhysicalDeviceQueueFamilyProperties2(m_handle, &numQueueFamilyProperties, nullptr);

		m_queueFamilyPropertiesLists.resize(numQueueFamilyProperties);
		m_queueFamilyProperties.resize(numQueueFamilyProperties);

		for(auto ix = 0; ix < numQueueFamilyProperties; ix++) {
			//Set structure types
			auto& queueFamilyProperties = m_queueFamilyProperties[ix];
			queueFamilyProperties.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;
			
			//Add structures
			auto& queueFamilyPropertiesList = m_queueFamilyPropertiesLists[ix];
			queueFamilyPropertiesList.Add(&queueFamilyProperties);
		}

		vkGetPhysicalDeviceQueueFamilyProperties2(m_handle, &numQueueFamilyProperties, m_queueFamilyProperties.data());
	}

	void PhysicalDevice::FindSupportedFeatures() {
		//Set structure types
		m_supportedFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
		m_supportedFeatures11.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
		m_supportedFeatures12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
		
		m_supportedDescriptorIndexingFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES;

		m_supportedMeshShaderFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_NV;

		//Add structures
		m_supportedFeaturesList.Add(&m_supportedFeatures);
		m_supportedFeaturesList.Add(&m_supportedFeatures11);
		if(IsVulkan12Supported()) m_supportedFeaturesList.Add(&m_supportedFeatures12);
		else {
			if(IsExtensionSupported(VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME)) m_supportedFeaturesList.Add(&m_supportedDescriptorIndexingFeatures);
		}

		if(IsExtensionSupported(VK_NV_MESH_SHADER_EXTENSION_NAME)) m_supportedFeaturesList.Add(&m_supportedMeshShaderFeatures);
		
		vkGetPhysicalDeviceFeatures2(m_handle, &m_supportedFeatures);
	}

	void PhysicalDevice::FindHasDedicatedMemory() {
		m_hasDedicatedMemory = true; //TODO: IMPL
	}

	u32 PhysicalDevice::FindDirectQueueFamilyIndex(Surface& surface) const {
		u32 numQueues = 0, familyIndex = 0;

		for(auto ix = 0; ix < m_queueFamilyProperties.size(); ix++) {
			const auto directFlags = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT;
			if(const auto& properties = m_queueFamilyProperties[ix].queueFamilyProperties; (properties.queueFlags & directFlags) == directFlags) {
				if(properties.queueCount > numQueues) {
					VkBool32 surfaceSupported = VK_FALSE;
					ThrowIfFailed(vkGetPhysicalDeviceSurfaceSupportKHR(m_handle, ix, surface, &surfaceSupported), "vkGetPhysicalDeviceSurfaceSupportKHR");
					if(surfaceSupported) {
						numQueues = properties.queueCount;
						familyIndex = ix;
					}
				}
			}
		}

		if(!numQueues) throw Exception("Failed to find direct queue family index");
		return familyIndex;
	}
	
	u32 PhysicalDevice::FindDedicatedComputeQueueFamilyIndex() const {
		u32 numQueues = 0, familyIndex = 0;
		
		for(auto ix = 0; ix < m_queueFamilyProperties.size(); ix++) {
			const auto& properties = m_queueFamilyProperties[ix].queueFamilyProperties;
			if((properties.queueFlags & VK_QUEUE_COMPUTE_BIT) == VK_QUEUE_COMPUTE_BIT && (properties.queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0) {
				if(properties.queueCount > numQueues) {
					numQueues = properties.queueCount;
					familyIndex = ix;
				}
			}
		}

		if(numQueues) return familyIndex;

		spdlog::warn("No dedicated compute queue found, using direct queue instead");
		return m_directQueueFamilyIndex;
	}

	u32 PhysicalDevice::FindDedicatedTransferQueueFamilyIndex() const {
		u32 numQueues = 0, familyIndex = 0;
		
		for(auto ix = 0; ix < m_queueFamilyProperties.size(); ix++) {
			const auto& properties = m_queueFamilyProperties[ix].queueFamilyProperties;
			const auto otherFlags = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT;
			if((properties.queueFlags & VK_QUEUE_TRANSFER_BIT) == VK_QUEUE_TRANSFER_BIT && (properties.queueFlags & otherFlags) == 0) {
				if(properties.queueCount > numQueues) {
					numQueues = properties.queueCount;
					familyIndex = ix;
				}
			}
		}

		if(numQueues) return familyIndex;

		spdlog::warn("No dedicated transfer queue found, using direct queue instead");
		return m_directQueueFamilyIndex;
	}

	void PhysicalDevice::FindSupportedExtensions() {
		u32 numSupportedExtensions;
		ThrowIfFailed(vkEnumerateDeviceExtensionProperties(m_handle, nullptr, &numSupportedExtensions, nullptr),
							"vkEnumerateDeviceExtensionProperties");

		m_supportedExtensions.resize(numSupportedExtensions);

		ThrowIfFailed(vkEnumerateDeviceExtensionProperties(m_handle, nullptr, &numSupportedExtensions, m_supportedExtensions.data()),
							"vkEnumerateDeviceExtensionProperties");
	}
	
	void PhysicalDevice::Create(VkPhysicalDevice physicalDevice, Surface& surface) {
		m_handle = physicalDevice;

		FindSupportedExtensions();
		
		FindProperties();
		FindMemoryProperties();
		FindQueueFamilyProperties();
		FindSupportedFeatures();
		FindHasDedicatedMemory();

		m_directQueueFamilyIndex = FindDirectQueueFamilyIndex(surface);
		m_dedicatedComputeQueueFamilyIndex = FindDedicatedComputeQueueFamilyIndex();
		m_dedicatedTransferQueueFamilyIndex = FindDedicatedTransferQueueFamilyIndex();

		SetInitialized();
	}

	bool PhysicalDevice::IsVulkan11Supported() const noexcept {
		const auto supportedVersion = m_properties.properties.apiVersion;

		const auto supportedMajor = VK_VERSION_MAJOR(supportedVersion), supportedMinor = VK_VERSION_MINOR(supportedVersion);
		return supportedMajor > 0 && supportedMinor > 0;
	}

	bool PhysicalDevice::IsVulkan12Supported() const noexcept {
		const auto supportedVersion = m_properties.properties.apiVersion;
		
		const auto supportedMajor = VK_VERSION_MAJOR(supportedVersion), supportedMinor = VK_VERSION_MINOR(supportedVersion);
		return supportedMajor > 0 && supportedMinor > 1;
	}

	bool PhysicalDevice::IsExtensionSupported(const char* name) const noexcept {
		KML_ASSERT(name);

		for(const auto& extension : m_supportedExtensions) {
			if(CString::AreStringsEqual(extension.extensionName, name)) return true;
		}

		return false;
	}
}

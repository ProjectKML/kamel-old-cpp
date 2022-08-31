//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanInstance.cpp
//------------------------------------------------------------

#include "VulkanInstance.hpp"
#include "Util/VulkanUtils.hpp"
#include "../../../Common/Util/String/CString.hpp"
#include "../../Core/Window/Window.hpp"
#include <SDL2/SDL_vulkan.h>
#include <spdlog/spdlog.h>

namespace KMLEngine::Vulkan {
	void Instance::OnDisposing() {
		if(m_validationLayersEnabled) {
			m_debugUtils.Dispose();
			m_validationLayersEnabled = false;
		}

		m_physicalDevices.clear();

		m_enabledExtensions.clear();
		m_enabledLayers.clear();

		m_supportedExtensions.clear();
		m_supportedLayers.clear();

		vkDestroyInstance(m_handle, GetAllocator());
		m_handle = VK_NULL_HANDLE;
	}

	void Instance::EnsureFeaturesSupported() {
		ThrowIfFailed(vkEnumerateInstanceVersion(&m_supportedVersion), "vkEnumerateInstanceVersion");

		const auto supportedMajor = VK_VERSION_MAJOR(m_supportedVersion), supportedMinor = VK_VERSION_MINOR(m_supportedVersion);
		if(supportedMinor < 1) throw Exception(fmt::format("Vulkan {}.{} not supported", 1, 1));
		if(supportedMinor < 2) {
			spdlog::warn("Vulkan {}.{} not supported", 1, 2);
			EnableVulkan12Extensions();
		}
	}

	void Instance::EnableVulkan12Extensions() {
		
	}

	void Instance::Initialize() {
		Loader::Load();
		EnsureFeaturesSupported();

		u32 numSupportedLayers;
		ThrowIfFailed(vkEnumerateInstanceLayerProperties(&numSupportedLayers, nullptr), "vkEnumerateInstanceLayerProperties");
		m_supportedLayers.resize(numSupportedLayers);
		ThrowIfFailed(vkEnumerateInstanceLayerProperties(&numSupportedLayers, m_supportedLayers.data()), "vkEnumerateInstanceLayerProperties");

		u32 numSupportedExtensions;
		ThrowIfFailed(vkEnumerateInstanceExtensionProperties(nullptr, &numSupportedExtensions, nullptr), "vkEnumerateInstanceExtensionProperties");
		m_supportedExtensions.resize(numSupportedExtensions);
		ThrowIfFailed(vkEnumerateInstanceExtensionProperties(nullptr, &numSupportedExtensions, m_supportedExtensions.data()), "vkEnumerateInstanceExtensionProperties");
	}

	void Instance::Create(bool requestValidationLayers) {
		KML_ASSERT(m_supportedVersion);

		u32 numSdlExtensions;
		auto& window = Window::GetInstance();

		if(!SDL_Vulkan_GetInstanceExtensions(window.GetHandle(), &numSdlExtensions, nullptr)) {
			throw Exception(fmt::format("{} failed: {}", "SDL_Vulkan_GetInstanceExtensions", SDL_GetError()));
		}

		m_sdlExtensions.resize(numSdlExtensions);
		if(!SDL_Vulkan_GetInstanceExtensions(window.GetHandle(), &numSdlExtensions, m_sdlExtensions.data())) {
			throw Exception(fmt::format("{} failed: {}", "SDL_Vulkan_GetInstanceExtensions", SDL_GetError()));
		}

		for(auto* extension : m_sdlExtensions) AddExtension(extension);

		if(requestValidationLayers) {
			if(TryAddLayer("VK_LAYER_KHRONOS_validation") && TryAddExtension("VK_EXT_debug_utils")) m_validationLayersEnabled = true;
		}

		const auto applicationInfo = Utils::ApplicationInfo(KML_ENGINE_GAME_NAME, VK_MAKE_VERSION(KML_ENGINE_GAME_VERSION_MAJOR, KML_ENGINE_GAME_VERSION_MINOR, KML_ENGINE_GAME_VERSION_PATCH),
		                                                    KML_ENGINE_NAME, VK_MAKE_VERSION(KML_ENGINE_VERSION_MAJOR, KML_ENGINE_VERSION_MINOR, KML_ENGINE_VERSION_PATCH), m_supportedVersion);

		const auto instanceCreateInfo = Utils::InstanceCreateInfo(&applicationInfo, static_cast<u32>(m_enabledLayers.size()), m_enabledLayers.data(),
		                                                          static_cast<u32>(m_enabledExtensions.size()), m_enabledExtensions.data());

		ThrowIfFailed(vkCreateInstance(&instanceCreateInfo, Vulkan::GetAllocator(), &m_handle), "vkCreateInstance");

		Loader::LoadInstance(m_handle);

		u32 numPhysicalDevices;
		ThrowIfFailed(vkEnumeratePhysicalDevices(m_handle, &numPhysicalDevices, nullptr), "vkEnumeratePhysicalDevices");

		m_physicalDevices.resize(numPhysicalDevices);
		ThrowIfFailed(vkEnumeratePhysicalDevices(m_handle, &numPhysicalDevices, m_physicalDevices.data()), "vkEnumeratePhysicalDevices");

		if(m_validationLayersEnabled) m_debugUtils.Create(*this);

		SetInitialized();
	}

	VkPhysicalDevice Instance::GetOptimalPhysicalDevice() const noexcept {
		VkDeviceSize highestHeapSize = 0;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

		for(auto currentPhysicalDevice : m_physicalDevices) {
			VkPhysicalDeviceProperties physicalDeviceProperties;
			vkGetPhysicalDeviceProperties(currentPhysicalDevice, &physicalDeviceProperties);

			if(physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
				VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
				vkGetPhysicalDeviceMemoryProperties(currentPhysicalDevice, &physicalDeviceMemoryProperties);

				VkDeviceSize heapSize = 0;
				for(usize iy = 0; iy < physicalDeviceMemoryProperties.memoryHeapCount; iy++) {
					const auto& currentHeap = physicalDeviceMemoryProperties.memoryHeaps[iy];
					if((currentHeap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) == VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) {
						heapSize += currentHeap.size;
					}
				}

				if(heapSize > highestHeapSize) {
					highestHeapSize = heapSize;
					physicalDevice = currentPhysicalDevice;
				}
			}
		}
		if(!physicalDevice) physicalDevice = m_physicalDevices[0];

		return physicalDevice;
	}

	bool Instance::TryAddLayer(const char* name) noexcept {
		KML_ASSERT(name);

		for(const auto& layer : m_supportedLayers) {
			if(CString::AreStringsEqual(layer.layerName, name)) {
				m_enabledLayers.push_back(name);
				return true;
			}
		}
		return false;
	}

	bool Instance::TryAddExtension(const char* name) noexcept {
		KML_ASSERT(name);

		for(const auto& extension : m_supportedExtensions) {
			if(CString::AreStringsEqual(extension.extensionName, name)) {
				m_enabledExtensions.push_back(name);
				return true;
			}
		}
		return false;
	}

	void Instance::AddLayer(const char* name) {
		KML_ASSERT(name);

		if(!TryAddLayer(name)) throw Exception(fmt::format("Layer not supported: {}", name));
	}

	void Instance::AddExtension(const char* name) {
		KML_ASSERT(name);

		if(!TryAddExtension(name)) throw Exception(fmt::format("Extension not supported: {}", name));
	}

	bool Instance::IsLayerEnabled(const char* name) const noexcept {
		KML_ASSERT(name);

		for(const auto* layer : m_enabledLayers) {
			if(CString::AreStringsEqual(layer, name)) return true;
		}
		return false;
	}

	bool Instance::IsExtensionEnabled(const char* name) const noexcept {
		KML_ASSERT(name);

		for(const auto* extension : m_enabledExtensions) {
			if(CString::AreStringsEqual(extension, name)) return true;
		}
		return false;
	}

	void Instance::PrintProperties() {
		spdlog::info("===== VULKAN INSTANCE =====");
		spdlog::info("Supported Vulkan layers:");
		for(const auto& layer : m_supportedLayers) {
			if(IsLayerEnabled(layer.layerName)) spdlog::info(reinterpret_cast<const char*>(u8"\t{} ✅"), layer.layerName);
			else spdlog::info("\t{}", layer.layerName);
		}

		spdlog::info("Vulkan instance extensions required by SDL2:");
		for(const auto* extension : m_sdlExtensions) spdlog::info("\t{}", extension);

		spdlog::info("Supported Vulkan instance extensions:");
		for(const auto& extension : m_supportedExtensions) {
			if(IsExtensionEnabled(extension.extensionName)) spdlog::info(reinterpret_cast<const char*>(u8"\t{} ✅"), extension.extensionName);
			else spdlog::info("\t{}", extension.extensionName);
		}
	}
}

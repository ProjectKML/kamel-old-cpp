//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanSurface.cpp
//------------------------------------------------------------

#include "VulkanSurface.hpp"
#include "VulkanInstance.hpp"
#include "Util/VulkanUtils.hpp"
#include "Util/VulkanTypes.hpp"
#include "../../Core/Window/Window.hpp"
#include <SDL2/SDL_vulkan.h>
#include <spdlog/spdlog.h>

namespace KMLEngine::Vulkan {
	void Surface::OnDisposing() {
		m_capabilities = {};

		m_supportedPresentModes.clear();
		m_supportedFormats.clear();

		vkDestroySurfaceKHR(m_instance->GetHandle(), m_handle, GetAllocator());
		m_handle = VK_NULL_HANDLE;

		m_physicalDeviceSurfaceInfo = {};
		
		m_instance = nullptr;
	}

	void Surface::FindCapabilities() {
		m_capabilities.sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR;
		m_capabilities.pNext = nullptr;

		//Add others here
		
		ThrowIfFailed(vkGetPhysicalDeviceSurfaceCapabilities2KHR(m_physicalDevice, &m_physicalDeviceSurfaceInfo, &m_capabilities), "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
	}
	
	void Surface::FindSurfaceFormats() {
		u32 numSurfaceFormats;
		ThrowIfFailed(vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, m_handle, &numSurfaceFormats, nullptr), "vkGetPhysicalDeviceSurfaceFormatsKHR");

		m_supportedFormats.resize(numSurfaceFormats);
		for(auto ix = 0; ix < numSurfaceFormats; ix++) {
			auto& surfaceFormat = m_supportedFormats[ix];
			surfaceFormat.sType = VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR;
			surfaceFormat.pNext = nullptr;

			//Add others here
		}
		
		ThrowIfFailed(vkGetPhysicalDeviceSurfaceFormats2KHR(m_physicalDevice, &m_physicalDeviceSurfaceInfo, &numSurfaceFormats, m_supportedFormats.data()), "vkGetPhysicalDeviceSurfaceFormatsKHR");
	}

	void Surface::FindPresentModes() {
		u32 numPresentModes;
		ThrowIfFailed(vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, m_handle, &numPresentModes, nullptr), "vkGetPhysicalDeviceSurfacePresentModesKHR");

		m_supportedPresentModes.resize(numPresentModes);
		ThrowIfFailed(vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, m_handle, &numPresentModes, m_supportedPresentModes.data()), "vkGetPhysicalDeviceSurfacePresentModesKHR");
	}
	
	void Surface::Create(Instance& instance, VkPhysicalDevice physicalDevice) {
		KML_ASSERT(physicalDevice);
		
		m_instance = &instance;
		m_physicalDevice = physicalDevice;

		if(auto& window = Window::GetInstance(); !SDL_Vulkan_CreateSurface(window.GetHandle(), instance.GetHandle(), &m_handle)) {
			throw Exception(fmt::format("{} failed: {}", "SDL_Vulkan_GetInstanceExtensions", SDL_GetError()));
		}

		m_physicalDeviceSurfaceInfo = Utils::PhysicalDeviceSurfaceInfo2KHR(m_handle);
		FindCapabilities();
		FindSurfaceFormats();
		FindPresentModes();
		
		SetInitialized();
	}

	
	void Surface::RefreshCapabilities() {
		ThrowIfFailed(vkGetPhysicalDeviceSurfaceCapabilities2KHR(m_physicalDevice, &m_physicalDeviceSurfaceInfo, &m_capabilities), "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
	}

	bool Surface::IsPresentModeSupported(VkPresentModeKHR presentMode) const noexcept {
		for(const auto mode : m_supportedPresentModes) if(mode == presentMode) return true;
		return false;
	}
	
	bool Surface::IsSurfaceFormatSupported(VkFormat format, VkColorSpaceKHR& colorSpace) const noexcept {
		for(const auto& surfaceFormat : m_supportedFormats) {
			if(surfaceFormat.surfaceFormat.format == format) {
				colorSpace = surfaceFormat.surfaceFormat.colorSpace;
				return true;
			}
		}
		return false;
	}
	
	void Surface::PrintProperties() {
		spdlog::info("===== VULKAN SURFACE =====");
		spdlog::info("Supported present modes:");
		for(const auto presentMode : m_supportedPresentModes) {
			spdlog::info("\t{}", Types::PresentMode::ToString(presentMode));
		}

		spdlog::info("Supported surface formats:");
		for(const auto& surfaceFormat : m_supportedFormats) {
			spdlog::info("\t{}: {}", Types::Format::ToString(surfaceFormat.surfaceFormat.format), Types::ColorSpace::ToString(surfaceFormat.surfaceFormat.colorSpace));
		}
	}
}

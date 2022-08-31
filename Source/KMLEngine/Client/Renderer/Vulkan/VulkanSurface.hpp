//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanSurface.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANSURFACE_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANSURFACE_HPP

#pragma once

#include "Util/VulkanObject.hpp"
#include <vector>

namespace KMLEngine::Vulkan {
    class Instance;

    class Surface final : public InstanceObject<VkSurfaceKHR, VK_OBJECT_TYPE_SURFACE_KHR>, public Disposable<Surface> {
        friend Disposable<Surface>;    
    private:
        VkPhysicalDeviceSurfaceInfo2KHR m_physicalDeviceSurfaceInfo = {};
        VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;

        std::vector<VkSurfaceFormat2KHR> m_supportedFormats;
        std::vector<VkPresentModeKHR> m_supportedPresentModes;

        //Capabilities
        VkSurfaceCapabilities2KHR m_capabilities = {};

        void FindCapabilities();
        void FindSurfaceFormats();
        void FindPresentModes();

        void OnDisposing();
    public:
        void Create(Instance& instance, VkPhysicalDevice physicalDevice);
        void RefreshCapabilities();

        bool IsPresentModeSupported(VkPresentModeKHR presentMode) const noexcept;
        bool IsSurfaceFormatSupported(VkFormat format, VkColorSpaceKHR& colorSpace) const noexcept;

        void PrintProperties();

        [[nodiscard]] KML_FORCEINLINE const std::vector<VkSurfaceFormat2KHR>& GetSupportedFormats() const noexcept { return m_supportedFormats; }
        [[nodiscard]] KML_FORCEINLINE const std::vector<VkPresentModeKHR>& GetPresentModes() const noexcept { return m_supportedPresentModes; }

        [[nodiscard]] KML_FORCEINLINE const VkSurfaceCapabilities2KHR& GetCapabilities() const noexcept { return m_capabilities; }
    };
}


#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANSURFACE_HPP

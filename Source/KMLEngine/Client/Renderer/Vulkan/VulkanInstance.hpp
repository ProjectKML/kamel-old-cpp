//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanInstance.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANINSTANCE_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANINSTANCE_HPP

#pragma once

#include "VulkanDebugUtils.hpp"
#include "../../../Common/Util/Traits/AddOrKeepPointer.hpp"
#include <vector>

namespace KMLEngine::Vulkan {
    class Instance final : public Object<VkInstance, VK_OBJECT_TYPE_INSTANCE>, public Disposable<Instance> {
        friend Disposable<Instance>;    
    private:
        std::vector<VkLayerProperties> m_supportedLayers;
        std::vector<VkExtensionProperties> m_supportedExtensions;
		
        std::vector<const char*> m_enabledLayers;
        std::vector<const char*> m_sdlExtensions;
        std::vector<const char*> m_enabledExtensions;

        std::vector<VkPhysicalDevice> m_physicalDevices;
        DebugUtils m_debugUtils;

        u32 m_supportedVersion = 0;
        bool m_validationLayersEnabled = false;

        void EnsureFeaturesSupported();
        void EnableVulkan12Extensions();
		
        void OnDisposing();
    public:
        void Initialize();
        void Create(bool requestValidationLayers);

        template<typename T>
        [[nodiscard]] KML_FORCEINLINE typename AddOrKeepPointer<T>::Type GetProcAddress(const char* name) noexcept {
            KML_ASSERT(name);
            return static_cast<typename AddOrKeepPointer<T>::Type>(vkGetInstanceProcAddr(m_handle, name));
        }

        [[nodiscard]] VkPhysicalDevice GetOptimalPhysicalDevice() const noexcept;

        bool TryAddLayer(const char* name) noexcept;
        bool TryAddExtension(const char* name) noexcept;

        void AddLayer(const char* name);
        void AddExtension(const char* name);

        [[nodiscard]] bool IsLayerEnabled(const char* name) const noexcept;
        [[nodiscard]] bool IsExtensionEnabled(const char* name) const noexcept;

        void PrintProperties();

        [[nodiscard]] KML_FORCEINLINE bool AreValidationLayersEnabled() const noexcept { return m_validationLayersEnabled; }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANINSTANCE_HPP

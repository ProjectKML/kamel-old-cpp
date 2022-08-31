//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RenderContext.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_RENDERCONTEXT_HPP
#define KMLENGINE_CLIENT_RENDERER_RENDERCONTEXT_HPP

#pragma once

#include "../../Common/Util/Traits/Singleton.hpp"
#include "Vulkan/VulkanInstance.hpp"
#include "Vulkan/VulkanSurface.hpp"
#include "Vulkan/VulkanPhysicalDevice.hpp"
#include "Vulkan/VulkanDevice.hpp"
#include "Vulkan/VulkanSwapchain.hpp"

#include "Common/Threading/RenderThreadManager.hpp"
#include "Common/Threading/RenderThreadTransferCollection.hpp"
#include "Common/Frame/RenderFrameManager.hpp"

namespace KMLEngine {
    class ResourceUploader;
    
    class RenderContext final : public Disposable<RenderContext>, public Singleton<RenderContext> {
        friend Disposable<RenderContext>;
    private:
        Vulkan::Instance m_instance;
        Vulkan::Surface m_surface;
        Vulkan::PhysicalDevice m_physicalDevice;
        Vulkan::Device m_device;
        Vulkan::Swapchain m_swapchain;

        RenderThreadManager<RenderThreadTransferCollection> m_transferManager;
        RenderFrameManager m_frameManager;

        ResourceUploader* m_resourceUploader;
        
        u32 m_debugLevel;

        void AddDeviceExtensions();
        void CreateDeviceAndSwapchain();
        void DestroyDeviceAndSwapchain();
		
        void OnDisposing();
    public:
        void Create(u32 debugLevel);
        void Update();

        //Getters
        [[nodiscard]] KML_FORCEINLINE u32 GetDebugLevel() const noexcept { return m_debugLevel; }

        [[nodiscard]] KML_FORCEINLINE Vulkan::Instance& GetVkInstance() noexcept { return m_instance; }
        [[nodiscard]] KML_FORCEINLINE const Vulkan::Instance& GetVkInstance() const noexcept { return m_instance; }

        [[nodiscard]] KML_FORCEINLINE Vulkan::Surface& GetSurface() noexcept { return m_surface; }
        [[nodiscard]] KML_FORCEINLINE const Vulkan::Surface& GetSurface() const noexcept { return m_surface; }

        [[nodiscard]] KML_FORCEINLINE Vulkan::PhysicalDevice& GetPhysicalDevice() noexcept { return m_physicalDevice; }
        [[nodiscard]] KML_FORCEINLINE const Vulkan::PhysicalDevice& GetPhysicalDevice() const noexcept { return m_physicalDevice; }

        [[nodiscard]] KML_FORCEINLINE Vulkan::Device& GetDevice() noexcept { return m_device; }
        [[nodiscard]] KML_FORCEINLINE const Vulkan::Device& GetDevice() const noexcept { return m_device; }

        [[nodiscard]] KML_FORCEINLINE Vulkan::Swapchain& GetSwapchain() noexcept { return m_swapchain; }
        [[nodiscard]] KML_FORCEINLINE const Vulkan::Swapchain& GetSwapchain() const noexcept { return m_swapchain; }

        [[nodiscard]] KML_FORCEINLINE RenderThreadManager<RenderThreadTransferCollection>& GetTransferManager() noexcept { return m_transferManager; }
        [[nodiscard]] KML_FORCEINLINE const RenderThreadManager<RenderThreadTransferCollection>& GetTransferManager() const noexcept { return m_transferManager; }

        [[nodiscard]] KML_FORCEINLINE RenderFrameManager& GetFrameManager() noexcept { return m_frameManager; }
        [[nodiscard]] KML_FORCEINLINE const RenderFrameManager& GetFrameManager() const noexcept { return m_frameManager; }

        [[nodiscard]] KML_FORCEINLINE ResourceUploader& GetResourceUploader() noexcept {
            KML_ASSERT(m_resourceUploader);
            return *m_resourceUploader;
        }

        [[nodiscard]] KML_FORCEINLINE const ResourceUploader& GetResourceUploader() const noexcept {
            KML_ASSERT(m_resourceUploader);
            return *m_resourceUploader;
        }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_RENDERCONTEXT_HPP

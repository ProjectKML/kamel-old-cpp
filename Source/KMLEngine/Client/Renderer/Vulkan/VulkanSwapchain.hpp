//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanSwapchain.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANSWAPCHAIN_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANSWAPCHAIN_HPP

#pragma once

#include "Image/VulkanRenderPass.hpp"
#include "Image/VulkanFramebuffer.hpp"

namespace KMLEngine::Vulkan {
    class ImageView;
    class Queue;
    class Semaphore;
    class Swapchain final : public SurfaceDeviceObject<VkSwapchainKHR, VK_OBJECT_TYPE_SWAPCHAIN_KHR>, public Disposable<Swapchain> {
        friend Disposable<Swapchain>;
    private:
        VkSurfaceFormatKHR m_usedSurfaceFormat = {};
        VkPresentModeKHR m_usedPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;

        u32 m_numImages = 0;
        VkImage* m_images = nullptr;
        ImageView* m_imageViews = nullptr;
        Framebuffer* m_framebuffers = nullptr;
        
        RenderPass m_renderPass;

        bool m_verticalSync = false, m_fullscreen = false;
        
        [[nodiscard]] VkPresentModeKHR FindOptimalPresentMode(bool verticalSync) const noexcept;
        [[nodiscard]] VkSurfaceFormatKHR FindOptimalSurfaceFormat() const;

        void CreateRenderPass();
        void CreateSwapchain(u32 width, u32 height, bool verticalSync, bool fullscreen);
        
        void OnDisposing();
    public:
        void Create(Device& device, Surface& surface, bool verticalSync, bool fullscreen);
        void Resize(u32 width, u32 height);

        [[nodiscard]] u32 AcquireNextImage(Semaphore& presentSemaphore);
        void Present(Queue& queue, Semaphore& renderSemaphore, u32 imageIndex);

        [[nodiscard]] KML_FORCEINLINE u32 GetNumImages() const noexcept { return m_numImages; }

        [[nodiscard]] KML_FORCEINLINE Framebuffer& GetFramebuffer(u32 index) noexcept { return m_framebuffers[index]; }
        [[nodiscard]] KML_FORCEINLINE const Framebuffer& GetFramebuffer(u32 index) const noexcept { return m_framebuffers[index]; }

        [[nodiscard]] KML_FORCEINLINE RenderPass& GetRenderPass() noexcept { return m_renderPass; }
        [[nodiscard]] KML_FORCEINLINE const RenderPass& GetRenderPass() const noexcept { return m_renderPass; }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANSWAPCHAIN_HPP

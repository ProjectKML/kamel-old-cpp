//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanSwapchain.cpp
//------------------------------------------------------------

#include "VulkanSwapchain.hpp"
#include "VulkanSurface.hpp"
#include "VulkanDevice.hpp"
#include "Synchronization/VulkanSemaphore.hpp"
#include "Image/VulkanImageView.hpp"
#include "Image/VulkanFramebuffer.hpp"
#include "../../Core/Window/Window.hpp"
#include <spdlog/spdlog.h>
#include <array>

namespace KMLEngine::Vulkan {
    void Swapchain::OnDisposing() {
        m_renderPass.Dispose();

        for(auto ix = 0; ix < m_numImages; ix++) {
            m_framebuffers[ix].Dispose();
            m_imageViews[ix].Dispose();
        }

        delete[] m_framebuffers;
        m_framebuffers = nullptr;
        
        delete[] m_imageViews;
        m_imageViews = nullptr;

        delete[] m_images;
        m_images = nullptr;

        m_usedPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
        m_usedSurfaceFormat = {};

        vkDestroySwapchainKHR(m_device->GetHandle(), m_handle, GetAllocator());
        m_handle = VK_NULL_HANDLE;

        m_device = nullptr;
        m_surface = nullptr;
    }

    VkPresentModeKHR Swapchain::FindOptimalPresentMode(bool verticalSync) const noexcept {
        if(verticalSync) return VK_PRESENT_MODE_FIFO_KHR;
        if(m_surface->IsPresentModeSupported(VK_PRESENT_MODE_IMMEDIATE_KHR)) return VK_PRESENT_MODE_IMMEDIATE_KHR;
        if(m_surface->IsPresentModeSupported(VK_PRESENT_MODE_MAILBOX_KHR)) return VK_PRESENT_MODE_MAILBOX_KHR;
        if(m_surface->IsPresentModeSupported(VK_PRESENT_MODE_FIFO_RELAXED_KHR)) return VK_PRESENT_MODE_FIFO_RELAXED_KHR;

        spdlog::error("Failed to find non-vertical sync present mode!");
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    static const std::array _AVAILABLE_FORMATS = {
        VK_FORMAT_B8G8R8A8_UNORM,
        VK_FORMAT_R8G8B8A8_UNORM,
        VK_FORMAT_B8G8R8A8_SRGB,
        VK_FORMAT_B8G8R8A8_SRGB
    };

    VkSurfaceFormatKHR Swapchain::FindOptimalSurfaceFormat() const {
        for(const auto format : _AVAILABLE_FORMATS) {
            VkColorSpaceKHR colorSpace;
            if(m_surface->IsSurfaceFormatSupported(format, colorSpace)) return VkSurfaceFormatKHR{format, colorSpace};
        }
        throw Exception("No suitable surface format found");
    }

    void Swapchain::CreateRenderPass() {
        RenderPass::SubpassBuilder subpassBuilder;
        subpassBuilder.AddColorAttachment(0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL).SetBindPoint(VK_PIPELINE_BIND_POINT_GRAPHICS);

        RenderPass::Builder builder;
        builder.AddSubpassDescription(subpassBuilder)
               .AddAttachmentDescription(m_usedSurfaceFormat.format,
                                         VK_SAMPLE_COUNT_1_BIT,
                                         VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                                         VK_ATTACHMENT_STORE_OP_STORE,
                                         VK_IMAGE_LAYOUT_UNDEFINED,
                                         VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

        m_renderPass.Create(*m_device, builder);
    }

    void Swapchain::CreateSwapchain(u32 width, u32 height, bool verticalSync, bool fullscreen) {
        const auto swapchainCreateInfo = Utils::SwapchainCreateInfoKHR(m_surface->GetHandle(), 3, m_usedSurfaceFormat.format, m_usedSurfaceFormat.colorSpace,
                                                                       Utils::Extent2D(width, height), 1, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
                                                                       m_usedPresentMode, VK_SHARING_MODE_EXCLUSIVE, 0, nullptr,
                                                                       VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR, VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR, VK_TRUE,
                                                                       m_handle);

        ThrowIfFailed(vkCreateSwapchainKHR(m_device->GetHandle(), &swapchainCreateInfo, GetAllocator(), &m_handle),
                              "vkCreateSwapchainKHR");

        ThrowIfFailed(vkGetSwapchainImagesKHR(m_device->GetHandle(), m_handle, &m_numImages, nullptr),
                              "vkGetSwapchainImagesKHR");

        m_images = new VkImage[m_numImages];
        m_imageViews = new ImageView[m_numImages];
        m_framebuffers = new Framebuffer[m_numImages];

        ThrowIfFailed(vkGetSwapchainImagesKHR(m_device->GetHandle(), m_handle, &m_numImages, m_images),
                              "vkGetSwapchainImagesKHR");

        const auto components = Utils::ComponentMapping();
        const auto subresourceRange = Utils::ImageSubresourceRange(VK_IMAGE_ASPECT_COLOR_BIT);

        for(auto ix = 0; ix < m_numImages; ix++) {
            auto& imageView = m_imageViews[ix];
            imageView.Create(*m_device, m_images[ix], VK_IMAGE_VIEW_TYPE_2D, m_usedSurfaceFormat.format,
                             components, subresourceRange);

            Framebuffer::Builder builder;
            builder.AddAttachment(imageView).SetSize(width, height, 1).SetRenderPass(m_renderPass);

            m_framebuffers[ix].Create(*m_device, builder);
        }
    }

    void Swapchain::Create(Device& device, Surface& surface, bool verticalSync, bool fullscreen) {
        m_device = &device;
        m_surface = &surface;

        m_verticalSync = verticalSync;
        m_fullscreen = fullscreen;

        surface.RefreshCapabilities();
        const auto& currentExtent = surface.GetCapabilities().surfaceCapabilities.currentExtent;

        m_usedPresentMode = FindOptimalPresentMode(verticalSync);
        m_usedSurfaceFormat = FindOptimalSurfaceFormat();

        CreateRenderPass();

        CreateSwapchain(currentExtent.width, currentExtent.height, verticalSync, fullscreen);

        SetInitialized();
    }

    void Swapchain::Resize(u32 width, u32 height) {
        m_device->WaitIdle();

        //Destroy old image views and frame buffers
        for(auto ix = 0; ix < m_numImages; ix++) {
            m_framebuffers[ix].Dispose();
            m_imageViews[ix].Dispose();
        }

        m_surface->RefreshCapabilities();
        const auto& currentExtent = m_surface->GetCapabilities().surfaceCapabilities.currentExtent;

        delete[] m_framebuffers;
        delete[] m_imageViews;

        const auto oldSwapchain = m_handle;

        CreateSwapchain(currentExtent.width, currentExtent.height, m_verticalSync, m_fullscreen);
        vkDestroySwapchainKHR(m_device->GetHandle(), oldSwapchain, GetAllocator());
    }

    u32 Swapchain::AcquireNextImage(Semaphore& presentSemaphore) {
    retry:
        u32 imageIndex;

        const auto result = vkAcquireNextImageKHR(m_device->GetHandle(), m_handle, std::numeric_limits<u64>::max(), presentSemaphore, VK_NULL_HANDLE, &imageIndex);
        if(result == VK_SUBOPTIMAL_KHR || result == VK_ERROR_OUT_OF_DATE_KHR) {
            auto& window = Window::GetInstance();
            Resize(window.GetWidth(), window.GetHeight());
            goto retry;
        }

        ThrowIfFailed(result, "vkAcquireNextImageKHR");

        return imageIndex;
    }

    void Swapchain::Present(Queue& queue, Semaphore& renderSemaphore, u32 imageIndex) {
        const auto presentInfo = Utils::PresentInfo(1, &renderSemaphore.GetHandle(), 1, &m_handle, &imageIndex, nullptr);

        auto result = vkQueuePresentKHR(queue, &presentInfo);
        if(result == VK_SUBOPTIMAL_KHR || result == VK_ERROR_OUT_OF_DATE_KHR) {
            auto& window = Window::GetInstance();
            Resize(window.GetWidth(), window.GetHeight());
        }
    }
}

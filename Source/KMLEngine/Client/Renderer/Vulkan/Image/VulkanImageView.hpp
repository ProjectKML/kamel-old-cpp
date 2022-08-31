//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanImageView.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_IMAGE_VULKANIMAGEVIEW_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_IMAGE_VULKANIMAGEVIEW_HPP

#pragma once

#include "../Util/VulkanObject.hpp"
#include "../Util/VulkanUtils.hpp"

namespace KMLEngine::Vulkan {
    class ImageView final : public DeviceObject<VkImageView, VK_OBJECT_TYPE_IMAGE_VIEW>, public Disposable<ImageView> {
        friend Disposable<ImageView>;
    private:
        VkImage m_image = VK_NULL_HANDLE;
        VkImageViewType m_viewType = VK_IMAGE_VIEW_TYPE_1D;
        VkFormat m_format = VK_FORMAT_UNDEFINED;
        VkComponentMapping m_components = {};
        VkImageSubresourceRange m_subresourceRange = {};
		
        void OnDisposing();
    public:
        void Create(Device& device, VkImage image, VkImageViewType viewType, VkFormat format,
            const VkComponentMapping& components = Utils::ComponentMapping(),
            const VkImageSubresourceRange& subresourceRange = Utils::ImageSubresourceRange(VK_IMAGE_ASPECT_COLOR_BIT));
		
        [[nodiscard]] KML_FORCEINLINE VkImageViewType GetViewType() const noexcept { return m_viewType; }
        [[nodiscard]] KML_FORCEINLINE VkFormat GetFormat() const noexcept { return m_format; }
        [[nodiscard]] KML_FORCEINLINE const VkComponentMapping& GetComponents() const noexcept { return m_components; }
        [[nodiscard]] KML_FORCEINLINE const VkImageSubresourceRange& GetSubresourceRange() const noexcept { return m_subresourceRange; }

        [[nodiscard]] KML_FORCEINLINE VkImage& GetImage() noexcept {
            KML_ASSERT(m_image);
            return m_image;
        }
        [[nodiscard]] KML_FORCEINLINE const VkImage& GetImage() const noexcept {
            KML_ASSERT(m_image);
            return m_image;
        }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_IMAGE_VULKANIMAGEVIEW_HPP
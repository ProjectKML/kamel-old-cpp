//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanImageView.cpp
//------------------------------------------------------------

#include "VulkanImageView.hpp"
#include "../Util/VulkanUtils.hpp"
#include "../VulkanDevice.hpp"

namespace KMLEngine::Vulkan {
    void ImageView::OnDisposing() {
        vkDestroyImageView(*m_device, m_handle, GetAllocator());
        m_handle = VK_NULL_HANDLE;

        m_subresourceRange = {};
        m_components = {};
        m_format = VK_FORMAT_UNDEFINED;
        m_viewType = VK_IMAGE_VIEW_TYPE_1D;
        m_image = VK_NULL_HANDLE;
		
        m_device = nullptr;
    }

    void ImageView::Create(Device& device, VkImage image, VkImageViewType viewType, VkFormat format, const VkComponentMapping& components,
        const VkImageSubresourceRange& subresourceRange) {
        KML_ASSERT(image);
		
        m_device = &device;

        m_image = image;
        m_viewType = viewType;
        m_format = format;
        m_components = components;
        m_subresourceRange = subresourceRange;

        const auto imageViewCreateInfo = Utils::ImageViewCreateInfo(image, viewType, format, subresourceRange, components);

        ThrowIfFailed(vkCreateImageView(device.GetHandle(), &imageViewCreateInfo, Vulkan::GetAllocator(), &m_handle),
                            "vkCreateImageView");
        SetInitialized();
    }
}

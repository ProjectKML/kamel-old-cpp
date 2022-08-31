//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanDescriptorUpdateTemplate.cpp
//------------------------------------------------------------

#include "VulkanDescriptorUpdateTemplate.hpp"
#include "../VulkanDevice.hpp"

namespace KMLEngine {
    void Vulkan::DescriptorUpdateTemplate::OnDisposing() {
        vkDestroyDescriptorUpdateTemplate(*m_device, m_handle, GetAllocator());
        m_handle = VK_NULL_HANDLE;

        m_device = nullptr;
    }
	
    void Vulkan::DescriptorUpdateTemplate::Create(Device& device, const Builder& builder) {
        m_device = &device;

        const auto descriptorUpdateTemplateCreateInfo = Utils::DescriptorUpdateTemplateCreateInfo(static_cast<u32>(builder.m_updateEntries.size()),
                                                                                                        builder.m_updateEntries.data(), builder.m_type, builder.m_descriptorSetLayout, builder.m_bindPoint, builder.m_pipelineLayout,
                                                                                                        builder.m_setIndex);

        ThrowIfFailed(vkCreateDescriptorUpdateTemplate(device, &descriptorUpdateTemplateCreateInfo, GetAllocator(),
                                                            &m_handle), "vkCreateDescriptorUpdateTemplate");

        SetInitialized();
    }
}
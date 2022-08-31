//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanPipeline.cpp
//------------------------------------------------------------

#include "VulkanPipeline.hpp"
#include "../VulkanDevice.hpp"
#include "../VulkanDeviceResources.hpp"

namespace KMLEngine::Vulkan {

    void Pipeline::OnDisposing() {
        vkDestroyPipeline(*m_device, m_handle, GetAllocator());
        m_handle = VK_NULL_HANDLE;

        m_device->GetResources().GetPipelineLayouts().Release(*m_pipelineLayout);
        m_pipelineLayout = nullptr;

        m_device = nullptr;
    }
}

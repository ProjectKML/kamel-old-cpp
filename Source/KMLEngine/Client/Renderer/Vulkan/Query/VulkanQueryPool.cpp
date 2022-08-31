//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanQueryPool.cpp
//------------------------------------------------------------

#include "VulkanQueryPool.hpp"
#include "../VulkanDevice.hpp"
#include "../Util/VulkanUtils.hpp"

namespace KMLEngine::Vulkan {
    void QueryPool::OnDisposing() {
        vkDestroyQueryPool(*m_device, m_handle, GetAllocator());
        m_handle = VK_NULL_HANDLE;

        m_device = nullptr;
    }

    void QueryPool::Create(Device& device, VkQueryType queryType, u32 queryCount, VkQueryPipelineStatisticFlags pipelineStatistics,
        VkQueryPoolCreateFlags flags) {
        m_device = &device;

        const auto queryPoolCreateInfo = Utils::QueryPoolCreateInfo(queryType, queryCount, pipelineStatistics, flags);

        ThrowIfFailed(vkCreateQueryPool(device, &queryPoolCreateInfo, GetAllocator(), &m_handle), "vkCreateQueryPool");

        SetInitialized();
    }
}

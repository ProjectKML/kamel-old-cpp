//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanQueryPool.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_QUERY_VULKANQUERYPOOL_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_QUERY_VULKANQUERYPOOL_HPP

#pragma once

#include "../Util/VulkanObject.hpp"

namespace KMLEngine::Vulkan {
	class QueryPool final : public DeviceObject<VkQueryPool, VK_OBJECT_TYPE_QUERY_POOL>, public Disposable<QueryPool> {
		friend Disposable<QueryPool>;
	private:
		void OnDisposing();
	public:
		void Create(Device& device, VkQueryType queryType, u32 queryCount, VkQueryPipelineStatisticFlags pipelineStatistics,
			VkQueryPoolCreateFlags flags = 0);
	};
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_QUERY_VULKANQUERYPOOL_HPP
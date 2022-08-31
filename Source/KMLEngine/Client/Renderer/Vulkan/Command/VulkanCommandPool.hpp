//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanCommandPool.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_COMMAND_COMMANDPOOL_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_COMMAND_COMMANDPOOL_HPP

#pragma once

#include "../Util/VulkanObject.hpp"

namespace KMLEngine::Vulkan {
	class Queue;
	class CommandPool final : public DeviceObject<VkCommandPool, VK_OBJECT_TYPE_COMMAND_POOL>, public Disposable<CommandPool> {
		friend Disposable<CommandPool>;
	private:
		void OnDisposing();
	public:
		void Create(Device& device, const VkCommandPoolCreateInfo& commandPoolCreateInfo);
		void Create(Device& device, Queue& queue, VkCommandPoolCreateFlags flags);

		void Reset(VkCommandPoolResetFlags commandPoolResetFlags);
	};
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_COMMAND_COMMANDPOOL_HPP
//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanFence.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_SYNCHRONIZATION_VULKANFENCE_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_SYNCHRONIZATION_VULKANFENCE_HPP

#pragma once

#include "../Util/VulkanObject.hpp"
#include "../Util/VulkanUtils.hpp"

namespace KMLEngine::Vulkan {
    class Fence final : public DeviceObject<VkFence, VK_OBJECT_TYPE_FENCE>, public Disposable<Fence> {
        friend Disposable<Fence>;    
    private:
        void OnDisposing();
    public:
        void Create(Device& device, const VkFenceCreateInfo& fenceCreateInfo);
        KML_FORCEINLINE void Create(Device& device, const void* next = nullptr, VkFenceCreateFlags flags = 0) {
            Create(device, Utils::FenceCreateInfo(next, flags));
        }

        void Reset();
        void WaitFor();

        [[nodiscard]] VkResult GetStatus() const;
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_SYNCHRONIZATION_VULKANFENCE_HPP
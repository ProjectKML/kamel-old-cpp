//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanSemaphore.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_SYNCHRONIZATION_VULKANSEMAPHORE_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_SYNCHRONIZATION_VULKANSEMAPHORE_HPP

#pragma once

#include "../Util/VulkanObject.hpp"
#include "../Util/VulkanUtils.hpp"

namespace KMLEngine::Vulkan {
    class Semaphore final : public DeviceObject<VkSemaphore, VK_OBJECT_TYPE_SEMAPHORE>, public Disposable<Semaphore> {
        friend Disposable<Semaphore>;    
    private:
        void OnDisposing();
    public:
        void Create(Device& device, const VkSemaphoreCreateInfo& semaphoreCreateInfo);
        KML_FORCEINLINE void Create(Device& device, const void* next = nullptr, VkSemaphoreCreateFlags flags = 0) {
            Create(device, Utils::SemaphoreCreateInfo(next, flags));
        }
    };
}
#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_SYNCHRONIZATION_VULKANSEMAPHORE_HPP
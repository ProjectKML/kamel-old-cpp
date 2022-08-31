//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanQueue.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANQUEUE_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANQUEUE_HPP

#pragma once

#include "Util/VulkanObject.hpp"
#include "../../../Common/Util/Math/Color4f.hpp"

namespace KMLEngine::Vulkan {
    class CommandBuffer;
    class Fence;
    class Queue final : public DeviceObject<VkQueue, VK_OBJECT_TYPE_QUEUE>, public Disposable<Queue> {
        friend Disposable<Queue>;
    private:
        u32 m_familyIndex;
		
        void OnDisposing();
    public:
        void Create(Device& device, VkQueue queue, u32 familyIndex);

        KML_FORCEINLINE void WaitIdle() { ThrowIfFailed(vkQueueWaitIdle(m_handle), "vkQueueWaitIdle"); }

        void Submit(const VkSubmitInfo& submitInfo);
        void Submit(const VkSubmitInfo& submitInfo, Fence& fence);

        void Submit(CommandBuffer& commandBuffer);
        void Submit(CommandBuffer& commandBuffer, Fence& fence);

        void Present(const VkPresentInfoKHR& presentInfo);

        void BeginDebugLabel(const char* name, const Color4f& color);
        void EndDebugLabel();

        [[nodiscard]] KML_FORCEINLINE u32 GetFamilyIndex() const noexcept { return m_familyIndex; }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANQUEUE_HPP

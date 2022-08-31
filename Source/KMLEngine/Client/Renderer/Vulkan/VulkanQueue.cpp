//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanQueue.cpp
//------------------------------------------------------------

#include "VulkanQueue.hpp"
#include "Synchronization/VulkanFence.hpp"
#include "Command/VulkanCommandBuffer.hpp"
#include "../RenderContext.hpp"

namespace KMLEngine::Vulkan {
    void Queue::OnDisposing() {
        m_handle = VK_NULL_HANDLE;
        m_device = nullptr;
    }
	
    void Queue::Create(Device& device, VkQueue queue, u32 familyIndex) {
        KML_ASSERT(queue);

        m_device = &device;
        m_handle = queue;
        m_familyIndex = familyIndex;
		
        SetInitialized();
    }
	
    void Queue::Submit(const VkSubmitInfo& submitInfo) {
        ThrowIfFailed(vkQueueSubmit(m_handle, 1, &submitInfo, VK_NULL_HANDLE), "vkQueueSubmit");
    }
	
    void Queue::Submit(const VkSubmitInfo& submitInfo, Fence& fence) {
        ThrowIfFailed(vkQueueSubmit(m_handle, 1, &submitInfo, fence), "vkQueueSubmit");
    }
	
    void Queue::Submit(CommandBuffer& commandBuffer) {
        const auto submitInfo = Utils::SubmitInfo(0, nullptr, nullptr, 1, &commandBuffer.GetHandle(), 0, nullptr);
        ThrowIfFailed(vkQueueSubmit(m_handle, 1, &submitInfo, VK_NULL_HANDLE), "vkQueueSubmit");
    }
	
    void Queue::Submit(CommandBuffer& commandBuffer, Fence& fence) {
        const auto submitInfo = Utils::SubmitInfo(0, nullptr, nullptr, 1, &commandBuffer.GetHandle(), 0, nullptr);
        ThrowIfFailed(vkQueueSubmit(m_handle, 1, &submitInfo, fence), "vkQueueSubmit");
    }
	
    void Queue::Present(const VkPresentInfoKHR& presentInfo) {
        ThrowIfFailed(vkQueuePresentKHR(m_handle, &presentInfo), "vkQueuePresentKHR");
    }

    void Queue::BeginDebugLabel(const char* name, const Color4f& color) {
        KML_ASSERT(name);

        if(RenderContext::GetInstance().GetVkInstance().AreValidationLayersEnabled()) {
            const auto debugUtilsLabel = Utils::DebugUtilsLabelEXT(name, color.R, color.G, color.B, color.A);

            vkQueueBeginDebugUtilsLabelEXT(m_handle, &debugUtilsLabel);
        }
    }

    void Queue::EndDebugLabel() {
        if(RenderContext::GetInstance().GetVkInstance().AreValidationLayersEnabled()) {
            vkQueueEndDebugUtilsLabelEXT(m_handle);
        }
    }
}

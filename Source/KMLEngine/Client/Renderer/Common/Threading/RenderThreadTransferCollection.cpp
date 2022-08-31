//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RenderThreadTransferCollection.cpp
//------------------------------------------------------------

#include "RenderThreadTransferCollection.hpp"
#include "../../Vulkan/VulkanDevice.hpp"

namespace KMLEngine {
    void RenderThreadTransferCollection::OnDisposing() {
        m_fence.Dispose();

        m_transferCommandBuffer.Dispose();
        m_transferCommandPool.Dispose();

        m_computeCommandBuffer.Dispose();
        m_computeCommandPool.Dispose();

        m_directCommandBuffer.Dispose();
        m_directCommandPool.Dispose();

        m_device = nullptr;
    }

    void RenderThreadTransferCollection::Create(Vulkan::Device& device) {
        m_device = &device;

        m_directCommandPool.Create(device, device.GetDirectQueue(), VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
        m_directCommandBuffer.AllocatePrimary(m_directCommandPool);

        m_computeCommandPool.Create(device, device.GetDedicateComputeQueue(), VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
        m_computeCommandBuffer.AllocatePrimary(m_computeCommandPool);

        m_transferCommandPool.Create(device, device.GetDedicatedTransferQueue(), VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
        m_transferCommandBuffer.AllocatePrimary(m_transferCommandPool);

        m_fence.Create(device);

        SetInitialized();
    }

    void RenderThreadTransferCollection::EndImmediateDirect() {
        m_directCommandBuffer.End();

        m_device->GetDirectQueue().Submit(m_directCommandBuffer, m_fence);

        m_fence.WaitFor();
        m_directCommandBuffer.Reset();
        m_directCommandPool.Reset(VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

        m_fence.Reset();
    }

    void RenderThreadTransferCollection::EndImmediateCompute() {
        m_computeCommandBuffer.End();

        m_device->GetDedicateComputeQueue().Submit(m_computeCommandBuffer, m_fence);

        m_fence.WaitFor();
        m_computeCommandBuffer.Reset();
        m_computeCommandPool.Reset(VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

        m_fence.Reset();
    }

    void RenderThreadTransferCollection::EndImmediateTransfer() {
        m_transferCommandBuffer.End();

        m_device->GetDedicatedTransferQueue().Submit(m_transferCommandBuffer, m_fence);

        m_fence.WaitFor();
        m_transferCommandBuffer.Reset();
        m_transferCommandPool.Reset(VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);

        m_fence.Reset();
    }
}

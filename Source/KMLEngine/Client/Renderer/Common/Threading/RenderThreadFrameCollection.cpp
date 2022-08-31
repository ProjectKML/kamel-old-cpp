//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RenderThreadFrameCollection.cpp
//------------------------------------------------------------

#include "RenderThreadFrameCollection.hpp"
#include "../../Vulkan/VulkanDevice.hpp"

namespace KMLEngine {
    void RenderThreadFrameCollection::OnDisposing() {
        m_commandBuffer.Dispose();
        m_commandPool.Dispose();
    }

    void RenderThreadFrameCollection::Create(Vulkan::Device& device, Vulkan::Queue& queue) {
        m_commandPool.Create(device, queue, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
        m_commandBuffer.AllocatePrimary(m_commandPool);
        
        SetInitialized();
    }
}

//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RenderFrameResources.cpp
//------------------------------------------------------------

#include "RenderFrameResources.hpp"
#include "../../Vulkan/VulkanDevice.hpp"

namespace KMLEngine {
	void RenderFrameResources::OnDisposing() {
	    m_frameFence.Dispose();

	    m_presentSemaphore.Dispose();
	    m_renderSemaphore.Dispose();

	    m_threadManager.Dispose();

	    m_commandBuffer.Dispose();
	    m_commandPool.Dispose();
	}
	
	void RenderFrameResources::Create(Vulkan::Device& device, usize frameIndex, usize numThreads) {
	    KML_ASSERT(numThreads);

	    m_device = &device;

	    m_commandPool.Create(device, device.GetDirectQueue(), VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
	    m_commandBuffer.AllocatePrimary(m_commandPool);

	    m_threadManager.Create(device, numThreads, device.GetDirectQueue());

	    m_renderSemaphore.Create(device);
	    m_presentSemaphore.Create(device);

	    m_frameFence.Create(device, nullptr, VK_FENCE_CREATE_SIGNALED_BIT);

	    m_frameIndex = frameIndex;

	    SetInitialized();
	}
}

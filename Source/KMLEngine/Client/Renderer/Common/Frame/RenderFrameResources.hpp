//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RenderFrameResources.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_FRAME_RENDERFRAMERESOURCES_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_FRAME_RENDERFRAMERESOURCES_HPP

#pragma once

#include "../../Vulkan/Command/VulkanCommandPool.hpp"
#include "../../Vulkan/Command/VulkanCommandBuffer.hpp"
#include "../../Vulkan/Synchronization/VulkanSemaphore.hpp"
#include "../../Vulkan/Synchronization/VulkanFence.hpp"
#include "../Threading/RenderThreadManager.hpp"
#include "../Threading/RenderThreadFrameCollection.hpp"

namespace KMLEngine {
	class RenderFrameResources final : public Disposable<RenderFrameResources> {
		friend Disposable<RenderFrameResources>;
	private:
		Vulkan::CommandPool m_commandPool;
		Vulkan::CommandBuffer m_commandBuffer;

	    RenderThreadManager<RenderThreadFrameCollection> m_threadManager;
	    
		Vulkan::Semaphore m_renderSemaphore, m_presentSemaphore;
		Vulkan::Fence m_frameFence;

		usize m_frameIndex = 0;
		Vulkan::Device* m_device = nullptr;

		void OnDisposing();
	public:
		void Create(Vulkan::Device& device, usize frameIndex, usize numThreads);

		[[nodiscard]] KML_FORCEINLINE Vulkan::CommandPool& GetCommandPool() noexcept { return m_commandPool; }
		[[nodiscard]] KML_FORCEINLINE const Vulkan::CommandPool& GetCommandPool() const noexcept { return m_commandPool; }

		[[nodiscard]] KML_FORCEINLINE Vulkan::CommandBuffer& GetCommandBuffer() noexcept { return m_commandBuffer; }
		[[nodiscard]] KML_FORCEINLINE const Vulkan::CommandBuffer& GetCommandBuffer() const noexcept { return m_commandBuffer; }

	    [[nodiscard]] KML_FORCEINLINE RenderThreadManager<RenderThreadFrameCollection>& GetThreadManager() noexcept { return m_threadManager; }
	    [[nodiscard]] KML_FORCEINLINE const RenderThreadManager<RenderThreadFrameCollection>& GetThreadManager() const noexcept { return m_threadManager; }

	    [[nodiscard]] KML_FORCEINLINE Vulkan::Semaphore& GetRenderSemaphore() noexcept { return m_renderSemaphore; }
	    [[nodiscard]] KML_FORCEINLINE const Vulkan::Semaphore& GetRenderSemaphore() const noexcept { return m_renderSemaphore; }

	    [[nodiscard]] KML_FORCEINLINE Vulkan::Semaphore& GetPresentSemaphore() noexcept { return m_presentSemaphore; }
	    [[nodiscard]] KML_FORCEINLINE const Vulkan::Semaphore& GetPresentSemaphore() const noexcept { return m_presentSemaphore; }

	    [[nodiscard]] KML_FORCEINLINE Vulkan::Fence& GetFrameFence() noexcept { return m_frameFence; }
	    [[nodiscard]] KML_FORCEINLINE const Vulkan::Fence& GetFrameFence() const noexcept { return m_frameFence; }

	    [[nodiscard]] KML_FORCEINLINE usize GetIndex() const noexcept { return m_frameIndex; }
	};
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_FRAME_RENDERFRAMERESOURCES_HPP

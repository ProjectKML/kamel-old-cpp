//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: GeometryBuffer.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_DEFERRED_GEOMETRYBUFFER_HPP
#define KMLENGINE_CLIENT_RENDERER_DEFERRED_GEOMETRYBUFFER_HPP

#pragma once

#include "../Common/Frame/RenderFrameCollection.hpp"
#include "../Vulkan/Synchronization/VulkanSemaphore.hpp"
#include "../Vulkan/Command/VulkanCommandBuffer.hpp"
#include "../Vulkan/Image/VulkanFramebuffer.hpp"
#include "../Vulkan/Image/VulkanImage.hpp"
#include "../Vulkan/Image/VulkanImageView.hpp"
#include "../Vulkan/Image/VulkanRenderPass.hpp"

namespace KMLEngine {
	class RenderContext;
	
	class GeometryBuffer final : public Disposable<GeometryBuffer>{
	    friend Disposable<GeometryBuffer>;
	public:
		class Frame final : public Disposable<Frame> {
		    friend Disposable<Frame>;
		private:
			Vulkan::Image m_diffuseImage;
			Vulkan::ImageView m_diffuseImageView;

			Vulkan::Image m_normalImage;
			Vulkan::ImageView m_normalImageView;

			Vulkan::Image m_specularImage;
			Vulkan::ImageView m_specularImageView;

			Vulkan::Image m_depthImage;
			Vulkan::ImageView m_depthImageView;

			Vulkan::Framebuffer m_framebuffer;

			Vulkan::CommandBuffer m_commandBuffer;
			Vulkan::Semaphore m_signalSemaphore;

			void OnDisposing();
		public:
			void Create(RenderFrameResources& currentFrame, RenderContext& context, Vulkan::RenderPass& renderPass, u32 width, u32 height);

			[[nodiscard]] KML_FORCEINLINE Vulkan::Image& GetDiffuseImage() noexcept { return m_diffuseImage; }
			[[nodiscard]] KML_FORCEINLINE const Vulkan::Image& GetDiffuseImage() const noexcept { return m_diffuseImage; }

			[[nodiscard]] KML_FORCEINLINE Vulkan::ImageView& GetDiffuseImageView() noexcept { return m_diffuseImageView; }
			[[nodiscard]] KML_FORCEINLINE const Vulkan::ImageView& GetDiffuseImageView() const noexcept { return m_diffuseImageView; }

			[[nodiscard]] KML_FORCEINLINE Vulkan::Image& GetNormalImage() noexcept { return m_normalImage; }
			[[nodiscard]] KML_FORCEINLINE const Vulkan::Image& GetNormalImage() const noexcept { return m_normalImage; }

			[[nodiscard]] KML_FORCEINLINE Vulkan::ImageView& GetNormalImageView() noexcept { return m_normalImageView; }
			[[nodiscard]] KML_FORCEINLINE const Vulkan::ImageView& GetNormalImageView() const noexcept { return m_normalImageView; }

			[[nodiscard]] KML_FORCEINLINE Vulkan::Image& GetSpecularImage() noexcept { return m_specularImage; }
			[[nodiscard]] KML_FORCEINLINE const Vulkan::Image& GetSpecularImage() const noexcept { return m_specularImage; }

			[[nodiscard]] KML_FORCEINLINE Vulkan::ImageView& GetSpecularImageView() noexcept { return m_specularImageView; }
			[[nodiscard]] KML_FORCEINLINE const Vulkan::ImageView& GetSpecularImageView() const noexcept { return m_specularImageView; }

			[[nodiscard]] KML_FORCEINLINE Vulkan::Image& GetDepthImage() noexcept { return m_depthImage; }
			[[nodiscard]] KML_FORCEINLINE const Vulkan::Image& GetDepthImage() const noexcept { return m_depthImage; }

			[[nodiscard]] KML_FORCEINLINE Vulkan::ImageView& GetDepthImageView() noexcept { return m_depthImageView; }
			[[nodiscard]] KML_FORCEINLINE const Vulkan::ImageView& GetDepthImageView() const noexcept { return m_depthImageView; }

			[[nodiscard]] KML_FORCEINLINE Vulkan::Framebuffer& GetFramebuffer() noexcept { return m_framebuffer; }
			[[nodiscard]] KML_FORCEINLINE const Vulkan::Framebuffer& GetFramebuffer() const noexcept { return m_framebuffer; }

			[[nodiscard]] KML_FORCEINLINE Vulkan::CommandBuffer& GetCommandBuffer() noexcept { return m_commandBuffer; }
			[[nodiscard]] KML_FORCEINLINE const Vulkan::CommandBuffer& GetCommandBuffer() const noexcept { return m_commandBuffer; }

			[[nodiscard]] KML_FORCEINLINE Vulkan::Semaphore& GetSignalSemaphore() noexcept { return m_signalSemaphore; }
			[[nodiscard]] KML_FORCEINLINE const Vulkan::Semaphore& GetSignalSemaphore() const noexcept { return m_signalSemaphore; }
		};
	private:
		Vulkan::RenderPass m_renderPass;
		RenderFrameCollection<Frame> m_frameCollection;

		void OnDisposing();
	public:
		void Create(RenderFrameManager& frameManager, RenderContext& context, u32 width, u32 height);
		void Resize(RenderFrameManager& frameManager, RenderContext& context, u32 newWidth, u32 newHeight);

		[[nodiscard]] KML_FORCEINLINE Vulkan::RenderPass& GetRenderPass() noexcept { return m_renderPass; }
		[[nodiscard]] KML_FORCEINLINE const Vulkan::RenderPass& GetRenderPass() const noexcept { return m_renderPass; }

		[[nodiscard]] KML_FORCEINLINE RenderFrameCollection<Frame>& GetFrameCollection() noexcept { return m_frameCollection; }
		[[nodiscard]] KML_FORCEINLINE const RenderFrameCollection<Frame>& GetFrameCollection() const noexcept { return m_frameCollection; }
	};
}


#endif //KMLENGINE_CLIENT_RENDERER_DEFERRED_GEOMETRYBUFFER_HPP

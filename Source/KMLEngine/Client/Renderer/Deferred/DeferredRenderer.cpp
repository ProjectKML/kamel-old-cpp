//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: DeferredRenderer.cpp
//------------------------------------------------------------

#include "DeferredRenderer.hpp"
#include "../Common/Frame/RenderFrameResources.hpp"
#include "../Common/Util/Settings/RenderSettingsManager.hpp"
#include "Geometry/GeometryRendererDefault.hpp"
#include "Geometry/GeometryRendererMeshShader.hpp"
#include "../Renderer.hpp"
#include "../Vulkan/VulkanDeviceResources.hpp"

namespace KMLEngine {
    //DeferredRenderer::FrameData
	void DeferredRenderer::Frame::OnDisposing() {
		m_finalImageDescriptorSet.Dispose();
	}

	void DeferredRenderer::Frame::Create(RenderFrameResources& currentFrame, RenderContext& context, Vulkan::Sampler& sampler, GeometryBuffer& geometryBuffer) {
		auto& device = context.GetDevice();
		auto& imageView = geometryBuffer.GetFrameCollection()[currentFrame].GetDiffuseImageView(); //TODO: final image

		Vulkan::DescriptorSet::Builder builder;
		builder.AddBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT);
		m_finalImageDescriptorSet.Create(device, builder);

		const auto descriptorImageInfo = Vulkan::Utils::DescriptorImageInfo(sampler, imageView, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		const auto writeDescriptorSet = Vulkan::Utils::WriteDescriptorSet(m_finalImageDescriptorSet, 0, 0, 1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		                                                                &descriptorImageInfo);

		m_finalImageDescriptorSet.Update(1, &writeDescriptorSet);

		SetInitialized();
	}

	void DeferredRenderer::Frame::Resize(RenderFrameResources& currentFrame, Vulkan::Sampler& sampler, GeometryBuffer& geometryBuffer) {
		auto& imageView = geometryBuffer.GetFrameCollection()[currentFrame].GetDiffuseImageView();

		const auto descriptorImageInfo = Vulkan::Utils::DescriptorImageInfo(sampler, imageView, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		const auto writeDescriptorSet = Vulkan::Utils::WriteDescriptorSet(m_finalImageDescriptorSet, 0, 0, 1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		                                                                &descriptorImageInfo);

		m_finalImageDescriptorSet.Update(1, &writeDescriptorSet);
	}

	//DeferredRenderer
	void DeferredRenderer::OnDisposing() {
	    delete m_geometryRenderer;
	    m_geometryRenderer = nullptr;

		m_frameCollection.Destroy();

        m_context->GetDevice().GetResources().GetSamplers().Release(*m_sampler);
        m_sampler = nullptr;
	    
		m_geometryBuffer.Dispose();

		m_settingsManager = nullptr;
		m_context = nullptr;
	}

	void DeferredRenderer::CreateClearValues() {
		for(auto ix = 0; ix < 3; ix++) m_clearValues[ix] = Vulkan::Utils::ClearValueFromColor(Colors4::CornflowerBlue);
		m_clearValues[3] = Vulkan::Utils::DepthStencilClearValue(0.0f, 0);
	}

    void DeferredRenderer::Create(RenderContext& context, RenderSettingsManager& settingsManager, u32 width, u32 height) {
        m_context = &context;
        m_settingsManager = &settingsManager;

        auto& device = context.GetDevice();
        auto& frameManager = context.GetFrameManager();

        //Create geometry buffer
        m_geometryBuffer.Create(frameManager, context, width, height);
        CreateClearValues();

        Vulkan::Sampler::Builder builder(VK_FILTER_LINEAR,
                                         VK_FILTER_LINEAR,
                                         VK_SAMPLER_MIPMAP_MODE_LINEAR,
                                         VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
                                         VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
                                         VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER);

        m_sampler = &device.GetResources().GetSamplers().Acquire(builder.GetDesc());
        m_frameCollection.Create(frameManager, context, *m_sampler, m_geometryBuffer);

        //Create geometry renderer
        const auto& supportedSettings = settingsManager.GetSupportedSettings();
        const auto& enabledSettings = settingsManager.GetEnabledSettings();

        if(supportedSettings.MeshShading && enabledSettings.MeshShading) {
            m_geometryRenderer = new GeometryRendererMeshShader(context, m_geometryBuffer);
        } else {
            m_geometryRenderer = new GeometryRendererDefault(context); //TODO: make this nice
        }

        SetInitialized();
    }

	void DeferredRenderer::Resize(u32 newWidth, u32 newHeight) {
	    auto& frameManager = m_context->GetFrameManager();

		m_geometryBuffer.Resize(frameManager, *m_context, newWidth, newHeight);
		m_frameCollection.ForEach(frameManager, [&](RenderFrameResources& currentFrame, Frame& frame) {
			frame.Resize(currentFrame, *m_sampler, m_geometryBuffer);
		});
	}

    void DeferredRenderer::ChangeSettings(const RenderSettings& oldSettings, const RenderSettings& newSettings) {
        //TODO:
    }

    void DeferredRenderer::Render(const RenderFrameResources& currentFrame, const TimerEventArgs& timerEventArgs, bool isSandbox) {
		auto& frameData = m_geometryBuffer.GetFrameCollection()[currentFrame];
		auto& commandBuffer = frameData.GetCommandBuffer();

		commandBuffer.Begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
		commandBuffer.BeginDebugLabel("Geometry Buffer", Color4f(0.022f, 0.372332f, 0.010f));
		commandBuffer.BeginRenderPass(frameData.GetFramebuffer(),
                                      static_cast<u32>(m_clearValues.size()),
                                      m_clearValues.data(),
                                      VK_SUBPASS_CONTENTS_INLINE);

		const auto size = frameData.GetFramebuffer().GetSize();
		
		const auto viewport = Vulkan::Utils::ViewportFromSize(size);
		const auto scissor = Vulkan::Utils::Rect2DFromSize(size);

		commandBuffer.SetViewport(0, 1, &viewport);
		commandBuffer.SetScissor(0, 1, &scissor); //TODO: maybe in 2methoden splitten damit es nicht so unübersichtlich ist
		
		m_geometryRenderer->Render(currentFrame, commandBuffer, timerEventArgs);
		
		commandBuffer.EndRenderPass();
		commandBuffer.EndDebugLabel();
		commandBuffer.End();

		const auto submitInfo = Vulkan::Utils::SubmitInfo(0, nullptr, nullptr, 1, &commandBuffer.GetHandle(), 1, &frameData.GetSignalSemaphore().GetHandle());

		auto& directQueue = m_context->GetDevice().GetDirectQueue();
		directQueue.Submit(submitInfo);
	}
}
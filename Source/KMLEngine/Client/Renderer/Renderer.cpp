//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Renderer.cpp
//------------------------------------------------------------

#include "Renderer.hpp"
#include "../Core/Window/Window.hpp"
#include "Common/Frame/RenderFrameResources.hpp"
#include "Deferred/DeferredRenderer.hpp"
#include "Deferred/FullscreenTriangleRenderer.hpp"

#include "Gui/ImGui/ImGuiRenderContext.hpp"

namespace KMLEngine {
    template<> Renderer* Singleton<Renderer>::_INSTANCE = nullptr;

    //Events (BEGIN)
    void Renderer::OnViewportResize(u32 width, u32 height) {
        auto& device = m_renderContext.GetDevice();
        device.WaitIdle();
        
        m_deferredRenderer->Resize(width, height);
    }

    void Renderer::OnSettingsChange(const RenderSettings& oldSettings, const RenderSettings& newSettings) {
        auto& device = m_renderContext.GetDevice();
        device.WaitIdle();

        m_deferredRenderer->ChangeSettings(oldSettings, newSettings);
    }
    //Events (END)

    Renderer::Renderer(u32 debugLevel) {
        m_renderContext.Create(debugLevel);

        m_settingsManager.Create(m_renderContext);
        m_viewportManager.Create();

        m_deferredRenderer = new DeferredRenderer;
        m_deferredRenderer->Create(m_renderContext, m_settingsManager, m_viewportManager.GetWidth(), m_viewportManager.GetHeight());

        m_fullscreenRenderer = new FullscreenTriangleRenderer;
        m_fullscreenRenderer->Create(m_renderContext, m_renderContext.GetSwapchain().GetRenderPass());

        m_imGuiContext = new ImGuiRenderContext;
        m_imGuiContext->Create();

        AttachSingleton();
    }

    Renderer::~Renderer() {
        DetachSingleton();

        m_renderContext.GetDevice().WaitIdle();

        m_imGuiContext->Dispose();
        delete m_imGuiContext;

        m_fullscreenRenderer->Dispose();
        delete m_fullscreenRenderer;

        m_deferredRenderer->Dispose();
        delete m_deferredRenderer;

        m_settingsManager.Dispose();
        m_renderContext.Dispose();
    }

    void Renderer::RenderRuntime(const TimerEventArgs& timerEventArgs) {
        auto& window = Window::GetInstance();
        if(window.IsMinimized()) return;

        if(m_viewportManager.Update()) OnViewportResize(m_viewportManager.GetWidth(), m_viewportManager.GetHeight());
        m_settingsManager.Update([this](const RenderSettings& oldSettings, const RenderSettings& newSettings) { OnSettingsChange(oldSettings, newSettings); });

        auto& frameManager = m_renderContext.GetFrameManager();
        auto& currentFrame = frameManager.BeginFrame(Colors4::CornflowerBlue);
        auto& commandBuffer = currentFrame.GetCommandBuffer();

        auto& deferredRendererFrame = m_deferredRenderer->GetFrameCollection()[currentFrame];
        auto& geometryBuffer = m_deferredRenderer->GetGeometryBuffer();
        auto& geometryBufferFrame = geometryBuffer.GetFrameCollection()[currentFrame];

        m_deferredRenderer->Render(currentFrame, timerEventArgs, false);
        m_fullscreenRenderer->Render(commandBuffer, deferredRendererFrame.GetFinalImageDescriptorSet());

        /*TODO: m_imGuiContext->NewFrame();

        ImGui::ShowDemoWindow(nullptr);

        m_imGuiContext->Render(commandBuffer);
        m_imGuiContext->EndFrame();*/

        frameManager.EndFrame(geometryBufferFrame.GetSignalSemaphore(), VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);

        m_renderContext.Update();
    }
}

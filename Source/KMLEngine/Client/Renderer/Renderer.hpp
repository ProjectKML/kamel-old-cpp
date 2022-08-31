//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Renderer.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_RENDERER_HPP
#define KMLENGINE_CLIENT_RENDERER_RENDERER_HPP

#pragma once

#include "RenderContext.hpp"
#include "Common/Util/Settings/RenderSettingsManager.hpp"
#include "Common/Util/ViewportSizeManager.hpp"

namespace KMLEngine {
    struct TimerEventArgs;

    class DeferredRenderer;
    class FullscreenTriangleRenderer;

    class ImGuiRenderContext;
    class Renderer final : public Uncopyable, public Singleton<Renderer> {
    private:
        RenderContext m_renderContext;
        RenderSettingsManager m_settingsManager;
        ViewportSizeManager m_viewportManager;

        DeferredRenderer* m_deferredRenderer = nullptr;
        FullscreenTriangleRenderer* m_fullscreenRenderer = nullptr;

        ImGuiRenderContext* m_imGuiContext = nullptr;

        //Events (BEGIN)
        void OnViewportResize(u32 width, u32 height);
        void OnSettingsChange(const RenderSettings& oldSettings, const RenderSettings& newSettings);
        //Events (END)
    public:
        explicit Renderer(u32 debugLevel);
        ~Renderer();

        void RenderRuntime(const TimerEventArgs& timerEventArgs);

        //Getter
        [[nodiscard]] KML_FORCEINLINE RenderSettingsManager& GetSettingsManager() noexcept { return m_settingsManager; }
        [[nodiscard]] KML_FORCEINLINE const RenderSettingsManager& GetSettingsManager() const noexcept { return m_settingsManager; }

        [[nodiscard]] KML_FORCEINLINE const ViewportSizeManager& GetViewportManager() const noexcept { return m_viewportManager; }

        [[nodiscard]] KML_FORCEINLINE DeferredRenderer& GetDeferredRenderer() noexcept {
            KML_ASSERT(m_deferredRenderer);
            return *m_deferredRenderer;
        }

        [[nodiscard]] KML_FORCEINLINE const DeferredRenderer& GetDeferredRenderer() const noexcept {
            KML_ASSERT(m_deferredRenderer);
            return *m_deferredRenderer;
        }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_RENDERER_HPP

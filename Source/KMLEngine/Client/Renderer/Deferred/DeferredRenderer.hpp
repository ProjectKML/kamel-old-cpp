//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: DeferredRenderer.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_DEFERRED_DEFERREDRENDERER_HPP
#define KMLENGINE_CLIENT_RENDERER_DEFERRED_DEFERREDRENDERER_HPP

#pragma once

#include "GeometryBuffer.hpp"
#include "../Vulkan/Descriptor/VulkanDescriptorSet.hpp"

namespace KMLEngine {
    struct TimerEventArgs;
    class RenderContext;
    class RenderSettingsManager;
    struct RenderSettings;
    class GeometryRenderer;

    class DeferredRenderer final : public Disposable<DeferredRenderer> {
        friend Disposable<DeferredRenderer>;
    public:
        class Frame final : public Disposable<Frame> {
            friend Disposable<Frame>;
        private:
            Vulkan::DescriptorSet m_finalImageDescriptorSet;

            void OnDisposing();
        public:
            void Create(RenderFrameResources& currentFrame, RenderContext& context, Vulkan::Sampler& sampler, GeometryBuffer& geometryBuffer); //TODO: statt gBuffer final image
            void Resize(RenderFrameResources& currentFrame, Vulkan::Sampler& sampler, GeometryBuffer& geometryBuffer);

            [[nodiscard]] KML_FORCEINLINE Vulkan::DescriptorSet& GetFinalImageDescriptorSet() noexcept { return m_finalImageDescriptorSet; }
            [[nodiscard]] KML_FORCEINLINE const Vulkan::DescriptorSet& GetFinalImageDescriptorSet() const noexcept { return m_finalImageDescriptorSet; }
        };
    private:
        //Geometry buffer
        GeometryBuffer m_geometryBuffer;
        std::array<VkClearValue, 4> m_clearValues;

        Vulkan::Sampler* m_sampler = nullptr;
        RenderFrameCollection<Frame> m_frameCollection;

        //Geometry renderer
        GeometryRenderer* m_geometryRenderer = nullptr;

        //Util
        RenderContext* m_context = nullptr;
        RenderSettingsManager* m_settingsManager = nullptr;

        void CreateClearValues();
        
        void OnDisposing();
    public:
        void Create(RenderContext& context, RenderSettingsManager& settingsManager, u32 width, u32 height);
        void Resize(u32 newWidth, u32 newHeight);
        void ChangeSettings(const RenderSettings& oldSettings, const RenderSettings& newSettings);

        void Render(const RenderFrameResources& currentFrame, const TimerEventArgs& timerEventArgs, bool isSandbox);
        
        [[nodiscard]] KML_FORCEINLINE GeometryBuffer& GetGeometryBuffer() noexcept { return m_geometryBuffer; }
        [[nodiscard]] KML_FORCEINLINE const GeometryBuffer& GetGeometryBuffer() const noexcept { return m_geometryBuffer; }

        [[nodiscard]] KML_FORCEINLINE RenderFrameCollection<Frame>& GetFrameCollection() noexcept { return m_frameCollection; }
        [[nodiscard]] KML_FORCEINLINE const RenderFrameCollection<Frame>& GetFrameCollection() const noexcept { return m_frameCollection; }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_DEFERRED_DEFERREDRENDERER_HPP

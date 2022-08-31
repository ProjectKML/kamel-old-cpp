//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanPipeline.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_PIPELINE_VULKANPIPELINE_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_PIPELINE_VULKANPIPELINE_HPP

#pragma once

#include "VulkanPipelineLayout.hpp"

namespace KMLEngine::Vulkan {
    class ShaderModule;
    class Pipeline : public DeviceObject<VkPipeline, VK_OBJECT_TYPE_PIPELINE>, public Disposable<Pipeline> {
        friend Disposable<Pipeline>;
    protected:
        PipelineLayout* m_pipelineLayout = nullptr;
        VkPipelineBindPoint m_bindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

        virtual void OnDisposing();

    public:
        [[nodiscard]] KML_FORCEINLINE PipelineLayout& GetLayout() noexcept {
            KML_ASSERT(m_pipelineLayout);
            return *m_pipelineLayout;
        }

        [[nodiscard]] KML_FORCEINLINE const PipelineLayout& GetLayout() const {
            KML_ASSERT(m_pipelineLayout);
            return *m_pipelineLayout;
        }

        [[nodiscard]] KML_FORCEINLINE VkPipelineBindPoint GetBindPoint() const noexcept { return m_bindPoint; }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_PIPELINE_VULKANPIPELINE_HPP

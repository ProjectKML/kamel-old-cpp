//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanComputePipeline.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_PIPELINE_VULKANCOMPUTEPIPELINE_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_PIPELINE_VULKANCOMPUTEPIPELINE_HPP

#pragma once

#include "VulkanPipeline.hpp"

namespace KMLEngine::Vulkan {
    class ComputePipeline final : public Pipeline {
    public:
        class Builder final {
            friend ComputePipeline;
        private:
            const ShaderModule* m_shaderModule = nullptr;
            VkPipelineShaderStageCreateInfo m_pipelineShaderStageCreateInfo = {};
        public:
            ~Builder() noexcept { Reset(); }

            KML_FORCEINLINE void Reset() noexcept {
                m_pipelineShaderStageCreateInfo = {};
                m_shaderModule = nullptr;
            }

            Builder& SetShaderStage(VkShaderStageFlagBits stage,
                const ShaderModule& shaderModule,
                const std::string_view& entryPoint,
                const VkSpecializationInfo* specializationInfo);
        };

        void Create(Device& device, const Builder& builder);
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_PIPELINE_VULKANCOMPUTEPIPELINE_HPP
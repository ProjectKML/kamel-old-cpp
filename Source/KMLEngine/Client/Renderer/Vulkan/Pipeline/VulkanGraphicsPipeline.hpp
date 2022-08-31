//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanGraphicsPipeline.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_PIPELINE_VULKANGRAPHICSPIPELINE_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_PIPELINE_VULKANGRAPHICSPIPELINE_HPP

#pragma once

#include "VulkanPipeline.hpp"
#include "../../../../Common/Util/STL/btree_set.hpp"
#include "../Util/VulkanUtils.hpp"

namespace KMLEngine::Vulkan {
    class GraphicsPipeline final : public Pipeline {
    public:
        class Builder final {
            friend GraphicsPipeline;
        private:
            std::vector<VkVertexInputBindingDescription> m_vertexInputBindingDescriptions;
            std::vector<VkVertexInputAttributeDescription> m_vertexInputAttributeDescriptions;

            kml_stl::btree_set<const ShaderModule*> m_shaderModules;
            std::vector<VkPipelineShaderStageCreateInfo> m_pipelineShaderStageCreateInfos;

            VkPipelineInputAssemblyStateCreateInfo m_pipelineInputAssemblyState = {};

            VkPipelineTessellationStateCreateInfo m_pipelineTessellationStateCreateInfo = {};
            VkBool32 m_tessellationStateUsed = VK_FALSE;

            std::vector<VkViewport> m_viewports;
            std::vector<VkRect2D> m_scissors;

            VkPipelineRasterizationStateCreateInfo m_pipelineRasterizationStateCreateInfo = {};
            VkPipelineMultisampleStateCreateInfo m_pipelineMultisampleStateCreateInfo = {};

            VkPipelineDepthStencilStateCreateInfo m_pipelineDepthStencilStateCreateInfo = {};
            VkBool32 m_depthStencilStateUsed = VK_FALSE;

            VkBool32 m_logicOpEnable = VK_FALSE;
            VkLogicOp m_logicOp = VK_LOGIC_OP_CLEAR;
            Color4f m_blendConstants = {};

            std::vector<VkPipelineColorBlendAttachmentState> m_pipelineColorBlendAttachmentStates;

            std::vector<VkDynamicState> m_dynamicStates;

            VkRenderPass m_renderPass = VK_NULL_HANDLE;
            u32 m_subpass = 0;
        public:
            ~Builder() noexcept { Reset(); }

            KML_FORCEINLINE void Reset() noexcept {
                m_subpass = 0;
                m_renderPass = VK_NULL_HANDLE;

                m_pipelineColorBlendAttachmentStates.clear();

                m_blendConstants = {};
                m_logicOp = VK_LOGIC_OP_CLEAR;
                m_logicOpEnable = VK_FALSE;

                m_depthStencilStateUsed = VK_FALSE;
                m_pipelineDepthStencilStateCreateInfo = {};

                m_pipelineMultisampleStateCreateInfo = {};
                m_pipelineRasterizationStateCreateInfo = {};

                m_scissors.clear();
                m_viewports.clear();

                m_tessellationStateUsed = VK_FALSE;
                m_pipelineTessellationStateCreateInfo = {};

                m_pipelineInputAssemblyState = {};

                m_pipelineShaderStageCreateInfos.clear();
                m_shaderModules.clear();

                m_vertexInputBindingDescriptions.clear();
                m_vertexInputAttributeDescriptions.clear();
            }

            KML_FORCEINLINE Builder& AddVertexInputBinding(u32 binding,
                                                           u32 stride,
                                                           VkVertexInputRate inputRate) noexcept {
                m_vertexInputBindingDescriptions.push_back(Utils::VertexInputBindingDescription(binding,
                                                                                                stride,
                                                                                                inputRate));
                return *this;
            }

            KML_FORCEINLINE Builder& AddVertexInputAttribute(u32 location,
                                                             u32 binding,
                                                             VkFormat format,
                                                             u32 offset) noexcept {
                m_vertexInputAttributeDescriptions.push_back(Utils::VertexInputAttributeDescription(location,
                                                                                                    binding,
                                                                                                    format,
                                                                                                    offset));
                return *this;
            }
            
            Builder& AddShaderStage(VkShaderStageFlagBits stage,
                const ShaderModule& shaderModule,
                const std::string_view& entryPoint,
                const VkSpecializationInfo* specializationInfo = nullptr);

            KML_FORCEINLINE Builder& SetInputAssemblyState(VkPrimitiveTopology topology,
                                                           VkBool32 primitiveRestartEnable = VK_FALSE) noexcept {
                m_pipelineInputAssemblyState = Utils::PipelineInputAssemblyStateCreateInfo(topology,
                                                                                           primitiveRestartEnable);
                return *this;
            }

            KML_FORCEINLINE Builder& SetTessellationState(u32 patchControlPoints) noexcept {
                m_pipelineTessellationStateCreateInfo = Utils::PipelineTessellationStateCreateInfo(patchControlPoints);
                m_tessellationStateUsed = VK_TRUE;

                return *this;
            }

            KML_FORCEINLINE Builder& AddViewport(const VkViewport& viewport) noexcept {
                m_viewports.push_back(viewport);
                return *this;
            }

            KML_FORCEINLINE Builder& AddViewport(f32 x,
                                                 f32 y,
                                                 f32 width,
                                                 f32 height,
                                                 f32 minDepth = 0.0f,
                                                 f32 maxDepth = 1.0f) noexcept {
                return AddViewport(Utils::Viewport(x,
                                                   y,
                                                   width,
                                                   height,
                                                   minDepth,
                                                   maxDepth));
            }

            KML_FORCEINLINE Builder& AddScissor(const VkRect2D& scissor) noexcept {
                m_scissors.push_back(scissor);
                return *this;
            }

            KML_FORCEINLINE Builder& AddScissor(i32 x,
                                                i32 y,
                                                u32 width,
                                                u32 height) noexcept {
                return AddScissor(Utils::Rect2D(x,
                                                y,
                                                width,
                                                height));
            }

            KML_FORCEINLINE Builder& SetRasterizationState(VkPolygonMode polygonMode,
                                                           VkCullModeFlags cullMode,
                                                           VkFrontFace frontFace,
                                                           VkBool32 depthClampEnable = VK_FALSE,
                                                           VkBool32 rasterizerDiscardEnable = VK_FALSE,
                                                           VkBool32 depthBiasEnable = VK_FALSE,
                                                           f32 depthBiasConstantFactor = 0.0f,
                                                           f32 depthBiasClamp = 0.0f,
                                                           f32 depthBiasSlopeFactor = 0.0f,
                                                           f32 lineWidth = 1.0f) noexcept {
                m_pipelineRasterizationStateCreateInfo = Utils::PipelineRasterizationStateCreateInfo(polygonMode,
                                                                                                     cullMode,
                                                                                                     frontFace,
                                                                                                     depthClampEnable,
                                                                                                     rasterizerDiscardEnable,
                                                                                                     depthBiasEnable,
                                                                                                     depthBiasConstantFactor,
                                                                                                     depthBiasClamp,
                                                                                                     depthBiasSlopeFactor,
                                                                                                     lineWidth);

                return *this;
            }

            KML_FORCEINLINE Builder& SetMultisampleState(VkSampleCountFlagBits rasterizationSamples,
                                                         VkBool32 sampleShadingEnable = VK_FALSE,
                                                         f32 minSampleShading = 0.0f,
                                                         const VkSampleMask* sampleMask = nullptr,
                                                         VkBool32 alphaToCoverageEnable = VK_FALSE,
                                                         VkBool32 alphaToOneEnable = VK_FALSE,
                                                         const void* next = nullptr,
                                                         VkPipelineMultisampleStateCreateFlags flags = 0) noexcept {
                m_pipelineMultisampleStateCreateInfo = Utils::PipelineMultisampleStateCreateInfo(rasterizationSamples,
                                                                                                 sampleShadingEnable,
                                                                                                 minSampleShading,
                                                                                                 sampleMask,
                                                                                                 alphaToCoverageEnable,
                                                                                                 alphaToOneEnable,
                                                                                                 next,
                                                                                                 flags);

                return *this;
            }

            KML_FORCEINLINE Builder& SetDepthStencilState(VkBool32 depthTestEnable,
                                                          VkBool32 depthWriteEnable,
                                                          VkCompareOp depthCompareOp,
                                                          VkBool32 depthBoundsTestEnable = VK_FALSE,
                                                          VkBool32 stencilTestEnable = VK_FALSE,
                                                          const VkStencilOpState& front = {},
                                                          const VkStencilOpState& back = {},
                                                          f32 minDepthBounds = 0.0f,
                                                          f32 maxDepthBounds = 1.0f) noexcept {
                m_pipelineDepthStencilStateCreateInfo = Utils::PipelineDepthStencilStateCreateInfo(depthTestEnable,
                                                                                                         depthWriteEnable,
                                                                                                         depthCompareOp,
                                                                                                         depthBoundsTestEnable,
                                                                                                         stencilTestEnable,
                                                                                                         front,
                                                                                                         back,
                                                                                                         minDepthBounds,
                                                                                                         maxDepthBounds);

                m_depthStencilStateUsed = VK_TRUE;

                return *this;
            }


            KML_FORCEINLINE Builder& SetColorBlendState(VkBool32 logicOpEnable = VK_FALSE,
                                                        VkLogicOp logicOp = VK_LOGIC_OP_NO_OP,
                                                        const Color4f& blendConstants = Color4f(1.0f, 0.0f, 1.0f, 0.0f)) noexcept {
                m_logicOpEnable = logicOpEnable;
                m_logicOp = logicOp;
                m_blendConstants = blendConstants;

                return *this;
            }

            KML_FORCEINLINE Builder& AddBlendAttachmentState(VkBool32 blendEnable = VK_FALSE,
                                                             VkBlendFactor srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
                                                             VkBlendFactor dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
                                                             VkBlendOp colorBlendOp = VK_BLEND_OP_ADD,
                                                             VkBlendFactor srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
                                                             VkBlendFactor dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
                                                             VkBlendOp alphaBlendOp = VK_BLEND_OP_ADD,
                                                             VkColorComponentFlags colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT) noexcept {
                m_pipelineColorBlendAttachmentStates.push_back(Utils::PipelineColorBlendAttachmentState(blendEnable,
                                                                                                        srcColorBlendFactor,
                                                                                                        dstColorBlendFactor,
                                                                                                        colorBlendOp,
                                                                                                        srcAlphaBlendFactor,
                                                                                                        dstAlphaBlendFactor,
                                                                                                        alphaBlendOp,
                                                                                                        colorWriteMask));

                return *this;
            }

            KML_FORCEINLINE Builder& AddDynamicState(VkDynamicState dynamicState) noexcept {
                m_dynamicStates.push_back(dynamicState);

                return *this;
            }

            KML_FORCEINLINE Builder& SetRenderPass(VkRenderPass renderPass,
                                                   u32 subpass = 0) noexcept {
                KML_ASSERT(renderPass);

                m_renderPass = renderPass;
                m_subpass = subpass;

                return *this;
            }
        };

        void Create(Device& device, const Builder& builder);
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_PIPELINE_VULKANGRAPHICSPIPELINE_HPP
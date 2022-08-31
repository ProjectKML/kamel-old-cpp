//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanGraphicsPipeline.cpp
//------------------------------------------------------------

#include "VulkanGraphicsPipeline.hpp"
#include "VulkanShaderModule.hpp"
#include "../VulkanDevice.hpp"
#include "../VulkanDeviceResources.hpp"
#include "../Util/SpirV/SpirVReflection.hpp"

namespace KMLEngine::Vulkan {
    GraphicsPipeline::Builder& GraphicsPipeline::Builder::AddShaderStage(VkShaderStageFlagBits stage, const ShaderModule& shaderModule, const std::string_view& entryPoint,
        const VkSpecializationInfo* specializationInfo) {
        m_shaderModules.insert(&shaderModule);
        m_pipelineShaderStageCreateInfos.push_back(Utils::PipelineShaderStageCreateInfo(stage, shaderModule, entryPoint.data(), specializationInfo));

        return *this;
    }

    void GraphicsPipeline::Create(Device& device, const Builder& builder) {
        m_device = &device;

        SpirV::ReflectedStages reflectedStages;
        SpirV::Reflection::ReflectStages(reflectedStages, builder.m_shaderModules);

        PipelineLayout::HashableDesc pipelineLayoutDesc;
        SpirV::Reflection::GetPipelineLayoutDesc(pipelineLayoutDesc, reflectedStages);

        m_pipelineLayout = &device.GetResources().GetPipelineLayouts().Acquire(pipelineLayoutDesc);
        m_bindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

        const auto pipelineVertexInputStateCreateInfo = Utils::PipelineVertexInputStateCreateInfo(static_cast<u32>(builder.m_vertexInputBindingDescriptions.size()),
                                                                                                        builder.m_vertexInputBindingDescriptions.data(),
                                                                                                        static_cast<u32>(builder.m_vertexInputAttributeDescriptions.size()),
                                                                                                        builder.m_vertexInputAttributeDescriptions.data());

        const auto pipelineViewportStateCreateInfo = Utils::PipelineViewportStateCreateInfo(static_cast<u32>(builder.m_viewports.size()),
                                                                                                  builder.m_viewports.data(),
                                                                                                  static_cast<u32>(builder.m_scissors.size()),
                                                                                                  builder.m_scissors.data());

        const auto pipelineColorBlendStateCreateInfo = Utils::PipelineColorBlendStateCreateInfo(builder.m_logicOpEnable,
                                                                                                      builder.m_logicOp,
                                                                                                      static_cast<u32>(builder.m_pipelineColorBlendAttachmentStates.size()),
                                                                                                      builder.m_pipelineColorBlendAttachmentStates.data(),
                                                                                                      builder.m_blendConstants.R,
                                                                                                      builder.m_blendConstants.G,
                                                                                                      builder.m_blendConstants.B,
                                                                                                      builder.m_blendConstants.A);

        const auto pipelineDynamicStateCreateInfo = Utils::PipelineDynamicStateCreateInfo(static_cast<u32>(builder.m_dynamicStates.size()),
                                                                                                builder.m_dynamicStates.data());

        const auto graphicsPipelineCreateInfo = Utils::GraphicsPipelineCreateInfo(static_cast<u32>(builder.m_pipelineShaderStageCreateInfos.size()),
                                                                                        builder.m_pipelineShaderStageCreateInfos.data(),
                                                                                        &pipelineVertexInputStateCreateInfo,
                                                                                        &builder.m_pipelineInputAssemblyState,
                                                                                        builder.m_tessellationStateUsed ? &builder.m_pipelineTessellationStateCreateInfo : nullptr, &pipelineViewportStateCreateInfo,
                                                                                        &builder.m_pipelineRasterizationStateCreateInfo, &builder.m_pipelineMultisampleStateCreateInfo,
                                                                                        builder.m_depthStencilStateUsed ? &builder.m_pipelineDepthStencilStateCreateInfo : nullptr,
                                                                                        &pipelineColorBlendStateCreateInfo,
                                                                                        &pipelineDynamicStateCreateInfo,
                                                                                        m_pipelineLayout->GetHandle(),
                                                                                        builder.m_renderPass,
                                                                                        builder.m_subpass);

        ThrowIfFailed(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &graphicsPipelineCreateInfo, GetAllocator(), &m_handle), "vkCreateGraphicsPipelines");

        SetInitialized();
    }
}
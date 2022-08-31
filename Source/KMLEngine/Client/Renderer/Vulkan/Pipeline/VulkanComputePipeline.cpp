//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanComputePipeline.cpp
//------------------------------------------------------------

#include "VulkanComputePipeline.hpp"
#include "VulkanShaderModule.hpp"
#include "../VulkanDevice.hpp"
#include "../VulkanDeviceResources.hpp"
#include "../Util/SpirV/SpirVReflection.hpp"

namespace KMLEngine::Vulkan {
    ComputePipeline::Builder& ComputePipeline::Builder::SetShaderStage(VkShaderStageFlagBits stage, const ShaderModule& shaderModule, const std::string_view& entryPoint,
        const VkSpecializationInfo* specializationInfo) {
        m_shaderModule = &shaderModule;
        m_pipelineShaderStageCreateInfo = Utils::PipelineShaderStageCreateInfo(stage, shaderModule, entryPoint.data(), specializationInfo);
        
        return *this;
    }

    void ComputePipeline::Create(Device& device, const Builder& builder) {
        m_device = &device;

        kml_stl::btree_set<const ShaderModule*> shaderModules = { builder.m_shaderModule };
        
        SpirV::ReflectedStages reflectedStages;
        SpirV::Reflection::ReflectStages(reflectedStages, shaderModules);

        PipelineLayout::HashableDesc pipelineLayoutDesc;
        SpirV::Reflection::GetPipelineLayoutDesc(pipelineLayoutDesc, reflectedStages);

        m_pipelineLayout = &device.GetResources().GetPipelineLayouts().Acquire(pipelineLayoutDesc);
        m_bindPoint = VK_PIPELINE_BIND_POINT_COMPUTE;

        const auto computePipelineCreateInfo = Utils::ComputePipelineCreateInfo(builder.m_pipelineShaderStageCreateInfo,
                                                                                *m_pipelineLayout);

        ThrowIfFailed(vkCreateComputePipelines(device, VK_NULL_HANDLE, 1, &computePipelineCreateInfo, GetAllocator(), &m_handle), "vkCreateComputePipelines");

        SetInitialized();
    }
}
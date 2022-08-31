//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanPipelineLayout.cpp
//------------------------------------------------------------

#include "VulkanPipelineLayout.hpp"
#include "../VulkanDevice.hpp"
#include "../VulkanDeviceResources.hpp"

namespace KMLEngine::Vulkan {
    void PipelineLayout::OnDisposing() {
        vkDestroyPipelineLayout(*m_device, m_handle, GetAllocator());
        m_handle = VK_NULL_HANDLE;

        auto& descriptorSetLayouts = m_device->GetResources().GetDescriptorSetLayouts();
        for(const auto& descriptorSetLayoutDesc : m_desc.SetLayouts) descriptorSetLayouts.Release(descriptorSetLayoutDesc);
        
        m_desc = {};

        m_device = nullptr;
    }

    void PipelineLayout::Create(Device& device, const HashableDesc& hashableDesc) {
        m_device = &device;
        m_desc = hashableDesc;
	    
        std::vector<VkDescriptorSetLayout> descriptorSetLayouts(hashableDesc.SetLayouts.size());
        for(auto ix = 0; ix < hashableDesc.SetLayouts.size(); ix++) {
            auto& descriptorSetLayout = device.GetResources().GetDescriptorSetLayouts().Acquire(hashableDesc.SetLayouts[ix]);
            descriptorSetLayouts[ix] = descriptorSetLayout;
        }

        std::vector<VkPushConstantRange> pushConstantRanges(hashableDesc.PushConstantRanges.size());
        for(auto ix = 0; ix < hashableDesc.PushConstantRanges.size(); ix++) {
            const auto& hashablePushConstantRange = hashableDesc.PushConstantRanges[ix];
            auto& pushConstantRange = pushConstantRanges[ix];

            pushConstantRange.stageFlags = hashablePushConstantRange.StageFlags;
            pushConstantRange.offset = hashablePushConstantRange.Offset;
            pushConstantRange.size = hashablePushConstantRange.Size;
        }

        const auto pipelineLayoutCreateInfo = Utils::PipelineLayoutCreateInfo(static_cast<u32>(descriptorSetLayouts.size()),
                                                                                    descriptorSetLayouts.data(), static_cast<u32>(pushConstantRanges.size()), pushConstantRanges.data());

        ThrowIfFailed(vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, GetAllocator(), &m_handle),
                              "vkCreatePipelineLayout");

        SetInitialized();
    }
}
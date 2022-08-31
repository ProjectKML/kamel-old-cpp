//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanDescriptorSet.cpp
//------------------------------------------------------------

#include "VulkanDescriptorSet.hpp"
#include "VulkanDescriptorUpdateTemplate.hpp"
#include "../VulkanDevice.hpp"
#include "../VulkanDeviceResources.hpp"

namespace KMLEngine::Vulkan {
    void DescriptorSet::OnDisposing() {
        m_device->GetResources().GetDescriptorSetLayouts().Release(m_descriptorSetLayoutDesc);
        m_handle = VK_NULL_HANDLE;

        m_device = nullptr;
    }

    void DescriptorSet::Create(Device& device, const DescriptorSetLayout::HashableDesc& hashableDesc, u32 descriptorCount) {
        m_device = &device;
        m_descriptorSetLayoutDesc = hashableDesc;

        auto& descriptorSetLayout = device.GetResources().GetDescriptorSetLayouts().Acquire(hashableDesc);

        const auto descriptorSetVariableDescriptorCountAllocateInfo = Utils::DescriptorSetVariableDescriptorCountAllocateInfo(
            1, &descriptorCount);
        const auto descriptorSetAllocateInfo = Utils::DescriptorSetAllocateInfo(
            device.GetDescriptorPool(), 1,
            &descriptorSetLayout.GetHandle(),
            descriptorCount ? &descriptorSetVariableDescriptorCountAllocateInfo : nullptr);

        ThrowIfFailed(vkAllocateDescriptorSets(device.GetHandle(), &descriptorSetAllocateInfo, &m_handle),
                      "vkAllocateDescriptorSets");

        SetInitialized();
    }

    void DescriptorSet::Update(u32 numWriteDescriptorSets, const VkWriteDescriptorSet* writeDescriptorSets, u32 numCopyDescriptorSets,
                               const VkCopyDescriptorSet* copyDescriptorSets) noexcept {
        KML_ASSERT((numWriteDescriptorSets && writeDescriptorSets) || (numCopyDescriptorSets && copyDescriptorSets));

        vkUpdateDescriptorSets(*m_device, numWriteDescriptorSets, writeDescriptorSets,
                               numCopyDescriptorSets, copyDescriptorSets);
    }

    void DescriptorSet::UpdateWithTemplate(DescriptorUpdateTemplate& descriptorUpdateTemplate, const void* data) noexcept {
        KML_ASSERT(data);

        vkUpdateDescriptorSetWithTemplate(*m_device, m_handle, descriptorUpdateTemplate, data);
    }
}

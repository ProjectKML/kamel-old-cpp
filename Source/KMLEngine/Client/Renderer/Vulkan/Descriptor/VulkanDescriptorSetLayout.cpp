//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanDescriptorSetLayout.cpp
//------------------------------------------------------------

#include "VulkanDescriptorSetLayout.hpp"
#include "../VulkanDevice.hpp"
#include "../VulkanDeviceResources.hpp"

namespace KMLEngine::Vulkan {
	void DescriptorSetLayout::OnDisposing() {
		vkDestroyDescriptorSetLayout(*m_device, m_handle, GetAllocator());
		m_handle = VK_NULL_HANDLE;

		auto& samplers = m_device->GetResources().GetSamplers();

		for(auto ix = 0; ix < m_desc.Bindings.size(); ix++) {
			const auto& hashableBindingDesc = m_desc.Bindings[ix];

			for(const auto& immutableSamplerDesc : hashableBindingDesc.ImmutableSamplers) samplers.Release(immutableSamplerDesc);
		}
		m_desc = {};

		m_device = nullptr;
	}

	void DescriptorSetLayout::Create(Device& device, const DescriptorSetLayout::HashableDesc& hashableDesc) {
		m_device = &device;
		m_desc = hashableDesc;

		std::vector<VkDescriptorSetLayoutBinding> bindings(hashableDesc.Bindings.size());

		auto numImmutableSamplers = 0, samplerIndex = 0;
		for(auto ix = 0; ix < bindings.size(); ix++) {
			if(const auto& hashableBindingDesc = hashableDesc.Bindings[ix]; !hashableBindingDesc.ImmutableSamplers.empty()) {
				numImmutableSamplers += hashableBindingDesc.DescriptorCount;
			}
		}

		std::vector<VkSampler> immutableSamplers(numImmutableSamplers);

		for(auto ix = 0; ix < bindings.size(); ix++) {
			const auto& hashableBindingDesc = hashableDesc.Bindings[ix];

			auto& bindingDesc = bindings[ix];
			bindingDesc.binding = hashableBindingDesc.Binding;
			bindingDesc.descriptorType = hashableBindingDesc.DescriptorType;
			bindingDesc.descriptorCount = hashableBindingDesc.DescriptorCount;
			bindingDesc.stageFlags = hashableBindingDesc.StageFlags;

			if(hashableBindingDesc.ImmutableSamplers.empty()) bindingDesc.pImmutableSamplers = nullptr;
			else {
				bindingDesc.pImmutableSamplers = &immutableSamplers[samplerIndex];

				for(usize iy = 0; iy < hashableBindingDesc.DescriptorCount; iy++) {
					immutableSamplers[samplerIndex++] = device.GetResources().GetSamplers().Acquire(hashableBindingDesc.ImmutableSamplers[iy]);
				}
			}
		}

		const auto descriptorSetLayoutBindingFlagsCreateInfo = Utils::DescriptorSetLayoutBindingFlagsCreateInfo(hashableDesc.BindingFlags.size(),
		                                                                                                        hashableDesc.BindingFlags.data());

		const auto descriptorSetLayoutCreateInfo = Utils::DescriptorSetLayoutCreateInfo(static_cast<u32>(bindings.size()),
		                                                                                bindings.data(),
		                                                                                hashableDesc.BindingFlags.empty() ? nullptr : &descriptorSetLayoutBindingFlagsCreateInfo);

		ThrowIfFailed(vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCreateInfo, GetAllocator(), &m_handle),
		                      "vkCreateDescriptorSetLayout");

		SetInitialized();
	}
}

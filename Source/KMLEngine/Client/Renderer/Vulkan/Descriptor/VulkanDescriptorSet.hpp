//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanDescriptorSet.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_DESCRIPTOR_VULKANDESCRIPTORSET_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_DESCRIPTOR_VULKANDESCRIPTORSET_HPP

#pragma once

#include "VulkanDescriptorSetLayout.hpp"

namespace KMLEngine::Vulkan {
	class DescriptorUpdateTemplate;
	class DescriptorSet final : public DeviceObject<VkDescriptorSet, VK_OBJECT_TYPE_DESCRIPTOR_SET>, public Disposable<DescriptorSet> {
		friend Disposable<DescriptorSet>;
	public:
		class Builder final {
		private:
			DescriptorSetLayout::HashableDesc m_desc;
			u32 m_descriptorCount = 0;
		public:
			~Builder() noexcept { Reset(); }
			KML_FORCEINLINE void Reset() noexcept {
				m_desc = {};
				m_descriptorCount = 0;
			}
			
			KML_FORCEINLINE Builder& AddBinding(u32 binding,
					VkDescriptorType descriptorType,
					u32 descriptorCount,
					VkShaderStageFlags stageFlags,
					std::vector<Sampler::HashableDesc> immutableSamplers = {}) noexcept {
				DescriptorSetLayout::HashableBindingDesc bindingDesc;
				bindingDesc.Binding = binding;
				bindingDesc.DescriptorType = descriptorType;
				bindingDesc.DescriptorCount = descriptorCount;
				bindingDesc.StageFlags = stageFlags;
				bindingDesc.ImmutableSamplers = std::move(immutableSamplers);

				m_desc.Bindings.push_back(bindingDesc);

				return *this;
			}

			KML_FORCEINLINE Builder& AddBindingFlags(VkDescriptorBindingFlags flags) noexcept {
				m_desc.BindingFlags.push_back(flags);

				return *this;
			}

			KML_FORCEINLINE Builder& SetDescriptorCount(u32 descriptorCount) noexcept {
				m_descriptorCount = descriptorCount;

				return *this;
			}
			
			
			[[nodiscard]] KML_FORCEINLINE const DescriptorSetLayout::HashableDesc& GetDesc() const noexcept { return m_desc; }
			[[nodiscard]] KML_FORCEINLINE u32 GetDescriptorCount() const noexcept { return m_descriptorCount; }
		};
	private:
		DescriptorSetLayout::HashableDesc m_descriptorSetLayoutDesc;
		
		void OnDisposing();
	public:
		void Create(Device& device, const DescriptorSetLayout::HashableDesc& hashableDesc, u32 descriptorCount);

		KML_FORCEINLINE void Create(Device& device, const Builder& builder) {
			Create(device, builder.GetDesc(), builder.GetDescriptorCount());
		}

		void Update(u32 numWriteDescriptorSets,
			const VkWriteDescriptorSet* writeDescriptorSets,
			u32 numCopyDescriptorSets = 0,
			const VkCopyDescriptorSet* copyDescriptorSets = nullptr) noexcept;
		
		void UpdateWithTemplate(DescriptorUpdateTemplate& descriptorUpdateTemplate, const void* data) noexcept;
	};
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_DESCRIPTOR_VULKANDESCRIPTORSET_HPP
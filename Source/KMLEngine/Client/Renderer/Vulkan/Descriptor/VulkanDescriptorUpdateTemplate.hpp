//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanDescriptorUpdateTemplate.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_DESCRIPTOR_VULKANDESCRIPTORUPDATETEMPLATE_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_DESCRIPTOR_VULKANDESCRIPTORUPDATETEMPLATE_HPP

#pragma once

#include "../Util/VulkanObject.hpp"
#include "../Util/VulkanUtils.hpp"
#include <vector>

namespace KMLEngine::Vulkan {
	class DescriptorUpdateTemplate final : public DeviceObject<VkDescriptorUpdateTemplate, VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE>, public Disposable<DescriptorUpdateTemplate> {
		friend Disposable<DescriptorUpdateTemplate>;
	public:
		class Builder final {
			friend class DescriptorUpdateTemplate;
		private:
			std::vector<VkDescriptorUpdateTemplateEntry> m_updateEntries;
			VkDescriptorUpdateTemplateType m_type = VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_DESCRIPTOR_SET;

			VkDescriptorSetLayout m_descriptorSetLayout = VK_NULL_HANDLE;

			VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
			VkPipelineBindPoint m_bindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

			u32 m_setIndex = 0;
		public:
			~Builder() noexcept { Reset(); }
			KML_FORCEINLINE void Reset() noexcept {
				m_bindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
				m_pipelineLayout = VK_NULL_HANDLE;

				m_descriptorSetLayout = VK_NULL_HANDLE;

				m_type = VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_DESCRIPTOR_SET;
				m_updateEntries.clear();
			}

			KML_FORCEINLINE Builder& AddUpdateEntry(const VkDescriptorUpdateTemplateEntry& updateEntry) noexcept {
				m_updateEntries.push_back(updateEntry);
				return *this;
			}

			KML_FORCEINLINE Builder& AddUpdateEntry(u32 dstBinding,
			                                        u32 dstArrayElement,
			                                        u32 descriptorCount,
			                                        VkDescriptorType descriptorType,
			                                        usize offset,
			                                        usize stride) noexcept {
				return AddUpdateEntry(Utils::DescriptorUpdateTemplateEntry(dstBinding,
				                                                           dstArrayElement,
				                                                           descriptorCount,
				                                                           descriptorType,
				                                                           offset,
				                                                           stride));
			}

			KML_FORCEINLINE Builder& SetType(VkDescriptorUpdateTemplateType type) noexcept {
				m_type = type;
				return *this;
			}

			KML_FORCEINLINE Builder& SetDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout) noexcept {
				KML_ASSERT(descriptorSetLayout);

				m_descriptorSetLayout = descriptorSetLayout;
				return *this;
			}

			KML_FORCEINLINE Builder& SetPipelineLayout(VkPipelineLayout pipelineLayout, VkPipelineBindPoint bindPoint) noexcept {
				KML_ASSERT(pipelineLayout);

				m_pipelineLayout = pipelineLayout;
				m_bindPoint = bindPoint;

				return *this;
			}

			KML_FORCEINLINE Builder& SetIndex(u32 setIndex) noexcept {
				m_setIndex = setIndex;
				return *this;
			}
		};

	private:
		void OnDisposing();
	public:
		void Create(Device& device, const Builder& builder);
	};
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_DESCRIPTOR_VULKANDESCRIPTORUPDATETEMPLATE_HPP
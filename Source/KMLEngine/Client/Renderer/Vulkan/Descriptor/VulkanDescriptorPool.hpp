//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanDescriptorPool.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_DESCRIPTOR_VULKANDESCRIPTORPOOL_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_DESCRIPTOR_VULKANDESCRIPTORPOOL_HPP

#pragma once

#include "../Util/VulkanUtils.hpp"
#include "../Util/VulkanObject.hpp"

#include <vector>

namespace KMLEngine::Vulkan {
    class DescriptorPool final : public DeviceObject<VkDescriptorPool, VK_OBJECT_TYPE_DESCRIPTOR_POOL>, public Disposable<DescriptorPool> {
            friend Disposable<DescriptorPool>;
        public:
        class Builder final {
            friend class DescriptorPool;
        private:
            u32 m_maxSize = 0;
            std::vector<VkDescriptorPoolSize> m_poolSizes;
        public:
            ~Builder() noexcept { Reset(); }

            void Reset() noexcept {
                m_maxSize = 0;
                m_poolSizes.clear();
            }

            KML_FORCEINLINE Builder& AddPoolSize(VkDescriptorType descriptorType, u32 descriptorCount) noexcept {
                KML_ASSERT(descriptorCount);
				
                m_poolSizes.push_back(Utils::DescriptorPoolSize(descriptorType, descriptorCount));
                m_maxSize += descriptorCount;

                return *this;
            }

            template<typename Container>
            KML_FORCEINLINE Builder& AddPoolSizes(const Container& poolSizes) {
                for(const auto& poolSize : poolSizes) m_poolSizes.push_back(poolSize);

                return *this;
            }
        };
    private:
        void OnDisposing();
    public:
        void Create(Device& device, const VkDescriptorPoolCreateInfo& descriptorPoolCreateInfo);
		
        KML_FORCEINLINE void Create(Device& device, const Builder& builder) {
            const auto descriptorPoolCreateInfo = Utils::DescriptorPoolCreateInfo(builder.m_maxSize, static_cast<u32>(builder.m_poolSizes.size()),
                                                                                        builder.m_poolSizes.data());

            Create(device, descriptorPoolCreateInfo);
        }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_DESCRIPTOR_VULKANDESCRIPTORPOOL_HPP
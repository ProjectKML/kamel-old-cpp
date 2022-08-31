//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanDescriptorSetLayout.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_DESCRIPTOR_VULKANDESCRIPTORSETLAYOUT_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_DESCRIPTOR_VULKANDESCRIPTORSETLAYOUT_HPP

#pragma once

#include "../Image/VulkanSampler.hpp"
#include "../../../../Common/Util/STL/vector.hpp"

namespace KMLEngine::Vulkan {
    class DescriptorSetLayout final : public DeviceObject<VkDescriptorSetLayout, VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT>, public Disposable<DescriptorSetLayout> {
        friend Disposable<DescriptorSetLayout>;
    public:
        struct HashableBindingDesc {
            u32 Binding = 0;
            VkDescriptorType DescriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
            u32 DescriptorCount = 0;
            VkShaderStageFlags StageFlags = 0;
            std::vector<Sampler::HashableDesc> ImmutableSamplers;

            HashableBindingDesc() = default;
            HashableBindingDesc(u32 binding,
                                VkDescriptorType descriptorType,
                                u32 descriptorCount,
                                VkShaderStageFlags stageFlags,
                                std::vector<Sampler::HashableDesc> immutableSamplers) :
                    Binding(binding),
                    DescriptorType(descriptorType),
                    DescriptorCount(descriptorCount),
                    StageFlags(stageFlags),
                    ImmutableSamplers(std::move(immutableSamplers)) {};

            [[nodiscard]] KML_FORCEINLINE bool operator ==(const HashableBindingDesc& other) const noexcept {
                return Binding == other.Binding &&
                       DescriptorType == other.DescriptorType &&
                       DescriptorCount == other.DescriptorCount &&
                       StageFlags == other.StageFlags &&
                       ImmutableSamplers == other.ImmutableSamplers;
            }

            [[nodiscard]] KML_FORCEINLINE bool operator !=(const HashableBindingDesc& other) const noexcept {
                return Binding != other.Binding ||
                       DescriptorType != other.DescriptorType ||
                       DescriptorCount != other.DescriptorCount ||
                       StageFlags != other.StageFlags ||
                       ImmutableSamplers != other.ImmutableSamplers;
            }
        };

        struct HashableDesc {
            std::vector<HashableBindingDesc> Bindings;
            std::vector<VkDescriptorBindingFlags> BindingFlags;
            VkDescriptorSetLayoutCreateFlags Flags = 0;

            HashableDesc() = default;
            HashableDesc(std::vector<HashableBindingDesc> bindings,
                         std::vector<VkDescriptorBindingFlags> bindingFlags,
                         VkDescriptorSetLayoutCreateFlags flags) : Bindings(std::move(bindings)),
                                                                   BindingFlags(std::move(bindingFlags)),
                                                                   Flags(flags) {}

            [[nodiscard]] KML_FORCEINLINE bool operator ==(const HashableDesc& other) const noexcept {
                return Bindings == other.Bindings &&
                       BindingFlags == other.BindingFlags &&
                       Flags == other.Flags;
            }

            [[nodiscard]] KML_FORCEINLINE bool operator !=(const HashableDesc& other) const noexcept {
                return Bindings != other.Bindings ||
                       BindingFlags != other.BindingFlags ||
                       Flags != other.Flags;
            }
        };

        struct BindingIndex {
            u32 Set = 0;
            u32 Binding = 0;

            BindingIndex() = default;
            BindingIndex(u32 set, u32 binding) : Set(set), Binding(binding) {}

            [[nodiscard]] KML_FORCEINLINE bool operator <(const BindingIndex& other) const noexcept {
                if(Set < other.Set) return true;
                if(Set > other.Set) return false;
                return Binding < other.Binding;
            }

            [[nodiscard]] KML_FORCEINLINE bool operator <=(const BindingIndex& other) const noexcept {
                if(Set < other.Set) return true;
                if(Set > other.Set) return false;
                return Binding <= other.Binding;
            }

            [[nodiscard]] KML_FORCEINLINE bool operator >(const BindingIndex& other) const noexcept {
                if(Set < other.Set) return false;
                if(Set > other.Set) return true;
                return Binding > other.Binding;
            }

            [[nodiscard]] KML_FORCEINLINE bool operator >=(const BindingIndex& other) const noexcept {
                if(Set < other.Set) return false;
                if(Set > other.Set) return true;
                return Binding >= other.Binding;
            }

            [[nodiscard]] KML_FORCEINLINE bool operator ==(const BindingIndex& other) const noexcept {
                return Set == other.Set && Binding == other.Binding;
            }

            [[nodiscard]] KML_FORCEINLINE bool operator !=(const BindingIndex& other) const noexcept {
                return Set != other.Set || Binding != other.Binding;
            }
        };

        class Builder final {
        private:
            HashableDesc m_hashableDesc;

        public:
            ~Builder() noexcept { Reset(); }

            KML_FORCEINLINE void Reset() noexcept { m_hashableDesc = {}; }

            KML_FORCEINLINE Builder& AddBinding(u32 binding,
                                                VkDescriptorType descriptorType,
                                                u32 descriptorCount,
                                                VkShaderStageFlags stageFlags,
                                                std::vector<Sampler::HashableDesc> immutableSamplers = {}) noexcept {
                m_hashableDesc.Bindings.emplace_back(binding,
                                                     descriptorType,
                                                     descriptorCount,
                                                     stageFlags,
                                                     std::move(immutableSamplers));
                return *this;
            }

            KML_FORCEINLINE Builder& AddBindingFlags(VkDescriptorBindingFlags descriptorBindingFlags) {
                m_hashableDesc.BindingFlags.push_back(descriptorBindingFlags);
                return *this;
            }

            KML_FORCEINLINE Builder& SetFlags(VkDescriptorSetLayoutCreateFlags flags) noexcept {
                m_hashableDesc.Flags = flags;
                return *this;
            }

            [[nodiscard]] KML_FORCEINLINE const HashableDesc& GetDesc() const noexcept { return m_hashableDesc; }
        };
    private:
        HashableDesc m_desc = {};
        
        void OnDisposing();
    public:
        void Create(Device& device, const HashableDesc& hashableDesc);

        KML_FORCEINLINE void Create(Device& device, const Builder& builder) {
            Create(device, builder.GetDesc());
        }

        [[nodiscard]] KML_FORCEINLINE const HashableDesc& GetDesc() const noexcept { return m_desc; }
    };
};

namespace std {
    using namespace KMLEngine;
    using namespace Vulkan;

    template<>
    struct hash<DescriptorSetLayout::HashableBindingDesc> {
        KML_FORCEINLINE usize operator()(const DescriptorSetLayout::HashableBindingDesc& hashableBindingDesc) const noexcept {
            return HashCode::Combine(hashableBindingDesc.Binding,
                                     hashableBindingDesc.DescriptorType,
                                     hashableBindingDesc.DescriptorCount,
                                     hashableBindingDesc.StageFlags,
                                     hashableBindingDesc.ImmutableSamplers);
        }
    };

    template<>
    struct hash<DescriptorSetLayout::HashableDesc> {
        KML_FORCEINLINE usize operator()(const DescriptorSetLayout::HashableDesc& hashableDesc) const noexcept {
            return HashCode::Combine(hashableDesc.Bindings,
                                     hashableDesc.BindingFlags,
                                     hashableDesc.Flags);
        }
    };

    template<>
    struct hash<DescriptorSetLayout::BindingIndex> {
        KML_FORCEINLINE usize operator()(const DescriptorSetLayout::BindingIndex& index) const noexcept {
            return HashCode::Combine(index.Set, index.Binding);
        }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_DESCRIPTOR_VULKANDESCRIPTORSETLAYOUT_HPP
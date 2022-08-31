//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanPipelineLayout.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_PIPELINE_VULKANPIPELINELAYOUT_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_PIPELINE_VULKANPIPELINELAYOUT_HPP

#pragma once

#include "../Descriptor/VulkanDescriptorSetLayout.hpp"

namespace KMLEngine::Vulkan {
    class PipelineLayout final : public DeviceObject<VkPipelineLayout, VK_OBJECT_TYPE_PIPELINE_LAYOUT>, public Disposable<PipelineLayout> {
        friend Disposable<PipelineLayout>;
    public:
        struct HashablePushConstantRange {
            VkShaderStageFlags StageFlags = 0;
            u32 Offset = 0;
            u32 Size = 0;

            HashablePushConstantRange() = default;
            HashablePushConstantRange(VkShaderStageFlags stageFlags, u32 offset, u32 size) noexcept
                    : StageFlags(stageFlags), Offset(offset), Size(size) {}

            [[nodiscard]] KML_FORCEINLINE bool operator ==(const HashablePushConstantRange& other) const noexcept {
                return StageFlags == other.StageFlags && Offset == other.Offset && Size == other.Size;
            }

            [[nodiscard]] KML_FORCEINLINE bool operator !=(const HashablePushConstantRange& other) const noexcept {
                return StageFlags != other.StageFlags || Offset != other.Offset || Size != other.Size;
            }
        };

        struct HashableDesc {
            std::vector<DescriptorSetLayout::HashableDesc> SetLayouts;
            std::vector<HashablePushConstantRange> PushConstantRanges;

            HashableDesc() = default;
            HashableDesc(std::vector<DescriptorSetLayout::HashableDesc> setLayouts, std::vector<HashablePushConstantRange> pushConstantRanges) noexcept
                    : SetLayouts(std::move(setLayouts)), PushConstantRanges(std::move(pushConstantRanges)) {}

            [[nodiscard]] KML_FORCEINLINE bool operator ==(const HashableDesc& other) const noexcept {
                return SetLayouts == other.SetLayouts && PushConstantRanges == other.PushConstantRanges;
            }

            [[nodiscard]] KML_FORCEINLINE bool operator !=(const HashableDesc& other) const noexcept {
                return SetLayouts != other.SetLayouts || PushConstantRanges != other.PushConstantRanges;
            }
        };
    private:
        HashableDesc m_desc;
        
        void OnDisposing();
    public:
        void Create(Device& device, const HashableDesc& hashableDesc);

        [[nodiscard]] KML_FORCEINLINE const HashableDesc& GetDesc() const noexcept { return m_desc; }
    };
}

namespace std {
    using namespace KMLEngine;
    using namespace Vulkan;

    template<>
    struct hash<PipelineLayout::HashablePushConstantRange> {
        KML_FORCEINLINE usize operator ()(const PipelineLayout::HashablePushConstantRange& hashablePushConstantRange) const noexcept {
            return HashCode::Combine(hashablePushConstantRange.StageFlags, hashablePushConstantRange.Offset, hashablePushConstantRange.Size);
        }
    };

    template<>
    struct hash<PipelineLayout::HashableDesc> {
        KML_FORCEINLINE usize operator ()(const PipelineLayout::HashableDesc& hashableDesc) const noexcept {
            return HashCode::Combine(hashableDesc.SetLayouts, hashableDesc.PushConstantRanges);
        }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_PIPELINE_VULKANPIPELINELAYOUT_HPP
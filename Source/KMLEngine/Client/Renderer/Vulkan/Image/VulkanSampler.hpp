//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanSampler.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_IMAGE_VULKANSAMPLER_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_IMAGE_VULKANSAMPLER_HPP

#pragma once

#include "../Util/VulkanObject.hpp"
#include "../../../../Common/Util/HashCode.hpp"

namespace KMLEngine::Vulkan {
	class Sampler final : public DeviceObject<VkSampler, VK_OBJECT_TYPE_SAMPLER>, public Disposable<Sampler> {
		friend Disposable<Sampler>;
	public:
		struct HashableDesc {
			VkFilter MinFilter = VK_FILTER_NEAREST;
			VkFilter MagFilter = VK_FILTER_NEAREST;
			VkSamplerMipmapMode MipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
			VkSamplerAddressMode AddressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			VkSamplerAddressMode AddressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			VkSamplerAddressMode AddressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			f32 MipLodBias = 0.0f;
			VkBool32 AnisotropyEnable = VK_FALSE;
			f32 MaxAnisotropy = 0.0f;
			VkBool32 CompareEnable = VK_FALSE;
			VkCompareOp CompareOp = VK_COMPARE_OP_NEVER;
			f32 MinLod = 0.0f;
			f32 MaxLod = 0.0f;
			VkBorderColor BorderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
			VkBool32 UnnormalizedCoordinates = VK_FALSE;

			HashableDesc() = default;
			HashableDesc(VkFilter minFilter,
                VkFilter magFilter,
                VkSamplerMipmapMode mipmapMode,
                VkSamplerAddressMode addressModeU,
                VkSamplerAddressMode addressModeV,
                VkSamplerAddressMode addressModeW,
                f32 mipLodBias,
                VkBool32 anisotropyEnable,
                f32 maxAnisotropy,
                VkBool32 compareEnable,
                VkCompareOp compareOp,
                f32 minLod,
                f32 maxLod,
                VkBorderColor borderColor,
                VkBool32 unnormalizedCoordinates) : MinFilter(minFilter),
                    MagFilter(magFilter),
                    MipmapMode(mipmapMode),
                    AddressModeU(addressModeU),
                    AddressModeV(addressModeV),
                    AddressModeW(addressModeW),
                    MipLodBias(mipLodBias),
                    AnisotropyEnable(anisotropyEnable),
                    MaxAnisotropy(maxAnisotropy),
                    CompareEnable(compareEnable),
                    CompareOp(compareOp),
                    MinLod(minLod),
                    MaxLod(maxLod),
                    BorderColor(borderColor),
                    UnnormalizedCoordinates(unnormalizedCoordinates) {}

            [[nodiscard]] KML_FORCEINLINE bool operator ==(const HashableDesc& other) const noexcept {
                return MinFilter == other.MinFilter &&
                    MagFilter == other.MagFilter &&
                    MipmapMode == other.MipmapMode &&
                    AddressModeU == other.AddressModeU &&
                    AddressModeV == other.AddressModeV &&
                    AddressModeW == other.AddressModeW &&
                    MipLodBias == other.MipLodBias &&
                    AnisotropyEnable == other.AnisotropyEnable &&
                    MaxAnisotropy == other.MaxAnisotropy &&
                    CompareEnable == other.CompareEnable &&
                    CompareOp == other.CompareOp &&
                    MinLod == other.MinLod &&
                    MaxLod == other.MaxLod &&
                    BorderColor == other.BorderColor &&
                    UnnormalizedCoordinates == other.UnnormalizedCoordinates;
            }

            [[nodiscard]] KML_FORCEINLINE bool operator !=(const HashableDesc& other) const noexcept {
                return MinFilter != other.MinFilter ||
                    MagFilter != other.MagFilter ||
                    MipmapMode != other.MipmapMode ||
                    AddressModeU != other.AddressModeU ||
                    AddressModeV != other.AddressModeV ||
                    AddressModeW != other.AddressModeW ||
                    MipLodBias != other.MipLodBias ||
                    AnisotropyEnable != other.AnisotropyEnable ||
                    MaxAnisotropy != other.MaxAnisotropy ||
                    CompareEnable != other.CompareEnable ||
                    CompareOp != other.CompareOp ||
                    MinLod != other.MinLod ||
                    MaxLod != other.MaxLod ||
                    BorderColor != other.BorderColor ||
                    UnnormalizedCoordinates != other.UnnormalizedCoordinates;
            }
		};

	    class Builder final {
	    private:
	        HashableDesc m_desc;

	    public:
	        Builder(VkFilter minFilter,
                 VkFilter magFilter,
                 VkSamplerMipmapMode mipmapMode,
                 VkSamplerAddressMode addressModeU,
                 VkSamplerAddressMode addressModeV,
                 VkSamplerAddressMode addressModeW,
                 f32 mipLodBias = 0.0f,
                 VkBool32 anisotropyEnable = VK_FALSE,
                 f32 maxAnisotropy = 0.0f,
                 VkBool32 compareEnable = VK_FALSE,
                 VkCompareOp compareOp = VK_COMPARE_OP_NEVER,
                 f32 minLod = 0.0f,
                 f32 maxLod = 1.0f,
                 VkBorderColor borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK,
                 VkBool32 unnormalizedCoordinates = VK_FALSE) : m_desc(minFilter,
                                                                       magFilter,
                                                                       mipmapMode,
                                                                       addressModeU,
                                                                       addressModeV,
                                                                       addressModeW,
                                                                       mipLodBias,
                                                                       anisotropyEnable,
                                                                       maxAnisotropy,
                                                                       compareEnable,
                                                                       compareOp,
                                                                       minLod,
                                                                       maxLod,
                                                                       borderColor,
                                                                       unnormalizedCoordinates) {}
	        ~Builder() noexcept { Reset(); }
	        KML_FORCEINLINE void Reset() noexcept { m_desc = {}; }
	    	
	        [[nodiscard]] KML_FORCEINLINE const HashableDesc& GetDesc() const { return m_desc; }
	    };
	private:
	    HashableDesc m_desc;

		void OnDisposing();
	public:
	    void Create(Device& device, const HashableDesc& hashableDesc);

	    KML_FORCEINLINE void Create(Device& device, const Builder& builder) {
            Create(device, builder.GetDesc());
	    }

	    [[nodiscard]] KML_FORCEINLINE const HashableDesc& GetDesc() const noexcept { return m_desc; }
	};
}

namespace std {
    using namespace KMLEngine;
    using namespace KMLEngine::Vulkan;

    template<>
    struct hash<Sampler::HashableDesc> {
        KML_FORCEINLINE usize operator()(const Sampler::HashableDesc& hashableDesc) const noexcept {
            return HashCode::Combine(hashableDesc.MinFilter,
                                     hashableDesc.MagFilter,
                                     hashableDesc.MipmapMode,
                                     hashableDesc.AddressModeU,
                                     hashableDesc.AddressModeV,
                                     hashableDesc.AddressModeW,
                                     hashableDesc.MipLodBias,
                                     hashableDesc.AnisotropyEnable,
                                     hashableDesc.MaxAnisotropy,
                                     hashableDesc.CompareEnable,
                                     hashableDesc.CompareOp,
                                     hashableDesc.MinLod,
                                     hashableDesc.MaxLod,
                                     hashableDesc.BorderColor,
                                     hashableDesc.UnnormalizedCoordinates);
        }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_IMAGE_VULKANSAMPLER_HPP
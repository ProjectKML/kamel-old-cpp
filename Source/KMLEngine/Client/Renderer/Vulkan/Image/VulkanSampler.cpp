//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanSampler.cpp
//------------------------------------------------------------

#include "VulkanSampler.hpp"
#include "../VulkanDevice.hpp"

namespace KMLEngine::Vulkan {
    void Sampler::OnDisposing() {
        m_desc = {};

        vkDestroySampler(*m_device, m_handle, GetAllocator());
        m_handle = VK_NULL_HANDLE;

        m_device = nullptr;
    }

    void Sampler::Create(Device& device, const HashableDesc& hashableDesc) {
        m_device = &device;
        m_desc = hashableDesc;

        const auto samplerCreateInfo = Utils::SamplerCreateInfo(hashableDesc.MagFilter, hashableDesc.MinFilter, hashableDesc.MipmapMode,
                                                                      hashableDesc.AddressModeU, hashableDesc.AddressModeV, hashableDesc.AddressModeW, hashableDesc.MipLodBias, hashableDesc.AnisotropyEnable,
                                                                      hashableDesc.MaxAnisotropy, hashableDesc.CompareEnable, hashableDesc.CompareOp, hashableDesc.MinLod, hashableDesc.MaxLod,
                                                                      hashableDesc.BorderColor, hashableDesc.UnnormalizedCoordinates);

        ThrowIfFailed(vkCreateSampler(device.GetHandle(), &samplerCreateInfo, GetAllocator(), &m_handle), "vkCreateSampler");

        SetInitialized();
    }
}

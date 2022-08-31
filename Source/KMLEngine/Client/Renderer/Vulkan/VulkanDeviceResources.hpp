//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanDeviceResources.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANDEVICERESOURCES_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANDEVICERESOURCES_HPP

#pragma once

#include "../../../Common/Util/Registry/MutableHashRegistry.hpp"
#include "Pipeline/VulkanPipelineLayout.hpp"

namespace KMLEngine::Vulkan {
    class DeviceResources final : public Disposable<DeviceResources> {
        friend Disposable<DeviceResources>;
    public:
        using DescriptorSetLayoutRegistry = MutableHashRegistry<DescriptorSetLayout::HashableDesc, DescriptorSetLayout, Device>;
        using PipelineLayoutRegistry = MutableHashRegistry<PipelineLayout::HashableDesc, PipelineLayout, Device>;
        using SamplerRegistry = MutableHashRegistry<Sampler::HashableDesc, Sampler, Device>;
    private:
        DescriptorSetLayoutRegistry m_descriptorSetLayouts;
        PipelineLayoutRegistry m_pipelineLayouts;
        SamplerRegistry m_samplers;
        
        void OnDisposing();
    public:
        void Create(Device& device);
        void Update();

        [[nodiscard]] KML_FORCEINLINE DescriptorSetLayoutRegistry& GetDescriptorSetLayouts() noexcept { return m_descriptorSetLayouts; }
        [[nodiscard]] KML_FORCEINLINE PipelineLayoutRegistry& GetPipelineLayouts() noexcept { return m_pipelineLayouts; }
        [[nodiscard]] KML_FORCEINLINE SamplerRegistry& GetSamplers() noexcept { return m_samplers; }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_VULKANDEVICERESOURCES_HPP

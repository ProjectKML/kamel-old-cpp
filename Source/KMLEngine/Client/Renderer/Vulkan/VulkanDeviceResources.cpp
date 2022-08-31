//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanDeviceResources.cpp
//------------------------------------------------------------

#include "VulkanDeviceResources.hpp"
#include "../RenderContext.hpp"

namespace KMLEngine::Vulkan {
    void DeviceResources::OnDisposing() {
        m_samplers.Dispose();
        m_pipelineLayouts.Dispose();
        m_descriptorSetLayouts.Dispose();
    }

    template<typename K, typename V, typename C>
    static std::function<void(typename MutableHashRegistry<K, V, C>::Reference*)> GetReleaseCallback() noexcept {
        return [](auto* value) {
            auto& frameManager = RenderContext::GetInstance().GetFrameManager();
            frameManager.AddFrameCompletionTask([value] {
                value->Object.Dispose();
                delete value;
            });
        };
    } 

    void DeviceResources::Create(Device& device) {
        m_descriptorSetLayouts.Create(device, GetReleaseCallback<DescriptorSetLayout::HashableDesc, DescriptorSetLayout, Device>());
        m_pipelineLayouts.Create(device, GetReleaseCallback<PipelineLayout::HashableDesc, PipelineLayout, Device>());
        m_samplers.Create(device,GetReleaseCallback<Sampler::HashableDesc, Sampler, Device>());
        
        SetInitialized();
    }

    void DeviceResources::Update() {
        m_descriptorSetLayouts.Update();
        m_pipelineLayouts.Update();
        m_samplers.Update();
    }
}

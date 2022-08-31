//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanShaderModule.cpp
//------------------------------------------------------------

#include "VulkanShaderModule.hpp"
#include "../Util/VulkanUtils.hpp"
#include "../VulkanDevice.hpp"

namespace KMLEngine::Vulkan {
    void ShaderModule::OnDisposing() {
        m_byteCode = {};
        m_location = {};

        vkDestroyShaderModule(*m_device, m_handle, GetAllocator());
        m_handle = VK_NULL_HANDLE;

        m_device = nullptr;
    }

    void ShaderModule::Create(Device& device, const PackageLocation& location) {
        KML_ASSERT(location);

        m_device = &device;

        m_location = location;
        location.GetEntry(m_byteCode);

        const auto shaderModuleCreateInfo = Utils::ShaderModuleCreateInfo(m_byteCode.size(), reinterpret_cast<u32*>(m_byteCode.data()));
        ThrowIfFailed(vkCreateShaderModule(device, &shaderModuleCreateInfo, GetAllocator(), &m_handle), "vkCreateShaderModule");

        SetInitialized();
    }
}

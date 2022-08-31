//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanShaderModule.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_PIPELINE_VULKANSHADERMODULE_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_PIPELINE_VULKANSHADERMODULE_HPP

#pragma once

#include "../Util/VulkanObject.hpp"
#include "../../../../Common/Core/Package/PackageLocation.hpp"
#include <vector>

namespace KMLEngine {
    class PackageLocation;

    namespace Vulkan {
        class ShaderModule final : public DeviceObject<VkShaderModule, VK_OBJECT_TYPE_SHADER_MODULE>, public Disposable<ShaderModule> {
            friend Disposable<ShaderModule>;
        private:
            std::vector<byte> m_byteCode;
            PackageLocation m_location;

            void OnDisposing();
        public:
            void Create(Device& device, const PackageLocation& location);
        
            [[nodiscard]] KML_FORCEINLINE const std::vector<byte>& GetByteCode() const noexcept { return m_byteCode; }
            [[nodiscard]] KML_FORCEINLINE const PackageLocation& GetLocation() const noexcept { return m_location; }
        };
    }
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_PIPELINE_VULKANSHADERMODULE_HPP

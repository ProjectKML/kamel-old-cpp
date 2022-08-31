//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RenderThreadFrameCollection.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_THREADING_RENDERTHREADFRAMECOLLECTION_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_THREADING_RENDERTHREADFRAMECOLLECTION_HPP

#pragma once

#include "../../Vulkan/Command/VulkanCommandPool.hpp"
#include "../../Vulkan/Command/VulkanCommandBuffer.hpp"

namespace KMLEngine {
    class RenderThreadFrameCollection final : public Disposable<RenderThreadFrameCollection> {
        friend Disposable<RenderThreadFrameCollection>;
    private:
        Vulkan::CommandPool m_commandPool;
        Vulkan::CommandBuffer m_commandBuffer;

        void OnDisposing();
    public:
        void Create(Vulkan::Device& device, Vulkan::Queue& queue);
        
        [[nodiscard]] KML_FORCEINLINE Vulkan::CommandPool& GetCommandPool() noexcept { return m_commandPool; }
        [[nodiscard]] KML_FORCEINLINE const Vulkan::CommandPool& GetCommandPool() const noexcept { return m_commandPool; }

        [[nodiscard]] KML_FORCEINLINE Vulkan::CommandBuffer& GetCommandBuffer() noexcept { return m_commandBuffer; }
        [[nodiscard]] KML_FORCEINLINE const Vulkan::CommandBuffer& GetCommandBuffer() const noexcept { return m_commandBuffer; }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_THREADING_RENDERTHREADFRAMECOLLECTION_HPP

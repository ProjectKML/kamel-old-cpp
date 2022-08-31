//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RenderThreadTransferCollection.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_THREADING_RENDERTHREADTRANSFERCOLLECTION_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_THREADING_RENDERTHREADTRANSFERCOLLECTION_HPP

#pragma once

#include "../../Vulkan/Command/VulkanCommandPool.hpp"
#include "../../Vulkan/Command/VulkanCommandBuffer.hpp"
#include "../../Vulkan/Synchronization/VulkanFence.hpp"

namespace KMLEngine {
    class RenderThreadTransferCollection final : public Disposable<RenderThreadTransferCollection>{
        friend Disposable<RenderThreadTransferCollection>;
    private:
        Vulkan::CommandPool m_directCommandPool;
        Vulkan::CommandBuffer m_directCommandBuffer;

        Vulkan::CommandPool m_computeCommandPool;
        Vulkan::CommandBuffer m_computeCommandBuffer;

        Vulkan::CommandPool m_transferCommandPool;
        Vulkan::CommandBuffer m_transferCommandBuffer;

        Vulkan::Fence m_fence;

        Vulkan::Device* m_device = nullptr;

        void OnDisposing();
    public:
        void Create(Vulkan::Device& device);

        [[nodiscard]] KML_FORCEINLINE Vulkan::CommandBuffer& BeginImmediateDirect() noexcept {
            m_directCommandBuffer.Begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
            return m_directCommandBuffer;
        }

        void EndImmediateDirect();

        [[nodiscard]] KML_FORCEINLINE Vulkan::CommandBuffer& BeginImmediateCompute() noexcept {
            m_computeCommandBuffer.Begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
            return m_computeCommandBuffer;
        }

        void EndImmediateCompute();

        [[nodiscard]] KML_FORCEINLINE Vulkan::CommandBuffer& BeginImmediateTransfer() noexcept {
            m_transferCommandBuffer.Begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
            return m_transferCommandBuffer;
        }

        void EndImmediateTransfer();
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_THREADING_RENDERTHREADTRANSFERCOLLECTION_HPP

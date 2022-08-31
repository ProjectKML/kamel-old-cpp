//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RenderFrameManager.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_FRAME_RENDERFRAMEMANAGER_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_FRAME_RENDERFRAMEMANAGER_HPP

#pragma once

#include "../../../../Common/Util/Traits/Disposable.hpp"
#include "../../../../Common/Util/Math/Color4f.hpp"
#include "../../Vulkan/Util/Vulkan.hpp"
#include <bitset>
#include <vector>
#include <functional>
#include <mutex>

namespace KMLEngine {
    namespace Vulkan {
        class Device;
        class Swapchain;
        class Semaphore;
    }

    class RenderFrameResources;
    class RenderFrameManager final : public Disposable<RenderFrameManager> {
        friend Disposable<RenderFrameManager>;
    public:
        static const usize NUM_MAX_FRAMES = 8;

        struct FrameCompletionTask {
            std::bitset<NUM_MAX_FRAMES> FrameRenderMask;
            std::function<void()> Function;

            FrameCompletionTask(const std::bitset<NUM_MAX_FRAMES>& frameRenderMask, std::function<void()> function) noexcept
                : FrameRenderMask(frameRenderMask), Function(function) {}
        };
    private:
        usize m_numFrameOverlaps = 0;
        usize m_frameCounter = 0;
        usize m_frameIndex = 0;
        usize m_swapchainIndex = 0;

        RenderFrameResources* m_resources;

        std::bitset<NUM_MAX_FRAMES> m_frameRenderMask;
        std::vector<FrameCompletionTask> m_frameCompletionTasks;
        std::mutex m_mutex;

        Vulkan::Device* m_device = nullptr;
        Vulkan::Swapchain* m_swapchain = nullptr;

        void ProcessFrameCompletedTasks();
        
        void OnDisposing();
    public:
        void Create(Vulkan::Device& device, Vulkan::Swapchain& swapchain, usize numFrameOverlaps, usize numThreads);

        RenderFrameResources& BeginFrame(const Color4f& clearColor);
        void EndFrame(Vulkan::Semaphore& waitSemaphore, VkPipelineStageFlags waitDstStageMask);

        void AddFrameCompletionTask(std::function<void()> function);
        void JoinFrameCompletionTasks();

        [[nodiscard]] RenderFrameResources& GetFrame(usize frameIndex) noexcept;
        [[nodiscard]] const RenderFrameResources& GetFrame(usize frameIndex) const noexcept;

        [[nodiscard]] KML_FORCEINLINE RenderFrameResources& GetCurrentFrame() noexcept { return GetFrame(m_frameIndex); }
        [[nodiscard]] KML_FORCEINLINE const RenderFrameResources& GetCurrentFrame() const noexcept { return GetFrame(m_frameIndex); }

        [[nodiscard]] KML_FORCEINLINE usize GetNumFrameOverlaps() const noexcept { return m_numFrameOverlaps; }
        [[nodiscard]] KML_FORCEINLINE usize GetFrameCounter() const noexcept { return m_frameCounter; }
        [[nodiscard]] KML_FORCEINLINE usize GetFrameIndex() const noexcept { return m_frameIndex; }
        [[nodiscard]] KML_FORCEINLINE usize GetSwapchainIndex() const noexcept { return m_swapchainIndex; }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_FRAME_RENDERFRAMEMANAGER_HPP
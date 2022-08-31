//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: RenderFrameManager.cpp
//------------------------------------------------------------

#include "RenderFrameManager.hpp"
#include "RenderFrameResources.hpp"
#include "RenderFrameCollection.hpp"
#include "../../Vulkan/VulkanDevice.hpp"
#include "../../Vulkan/VulkanSwapchain.hpp"

namespace KMLEngine {
    void RenderFrameManager::OnDisposing() {
        for(auto ix = 0; ix < m_numFrameOverlaps; ix++) m_resources[ix].Dispose();
        delete[] m_resources;
        m_resources = nullptr;

        KML_ASSERT(m_frameCompletionTasks.empty());
        m_frameRenderMask = {};

        m_swapchainIndex = 0;
        m_frameIndex = 0;
        m_frameCounter = 0;
        m_numFrameOverlaps = 0;
    }

    void RenderFrameManager::ProcessFrameCompletedTasks() {
        for(auto ix = 0; ix < m_frameCompletionTasks.size(); ix++) {
            auto& task = m_frameCompletionTasks[ix];
            auto& frameRenderMask = task.FrameRenderMask;

            frameRenderMask.set(m_frameIndex, false);

            if(!frameRenderMask.count()) {
                task.Function();

                std::scoped_lock lock(m_mutex);
                m_frameCompletionTasks.erase(m_frameCompletionTasks.begin() + ix--);
            }
        }
    }

    void RenderFrameManager::Create(Vulkan::Device& device, Vulkan::Swapchain& swapchain, usize numFrameOverlaps, usize numThreads) {
        m_device = &device;
        m_swapchain = &swapchain;

        KML_ASSERT(numFrameOverlaps < NUM_MAX_FRAMES);
        m_numFrameOverlaps = numFrameOverlaps;

        m_resources = new RenderFrameResources[m_numFrameOverlaps];
        for(auto ix = 0; ix < m_numFrameOverlaps; ix++) m_resources[ix].Create(device, ix, numThreads);

        m_frameCounter = 0;
        m_frameIndex = 0;

        SetInitialized();
    }


    RenderFrameResources& RenderFrameManager::BeginFrame(const Color4f& clearColor) {
        auto& currentFrame = GetCurrentFrame();

        //Wait until last frame is rendered
        auto& frameFence = currentFrame.GetFrameFence();
        frameFence.WaitFor();
        frameFence.Reset();

        //Set frame being no more rendered
        m_frameRenderMask.set(m_frameIndex, false);
        ProcessFrameCompletedTasks();

        //Now we can reset last frame resources
        auto& commandPool = currentFrame.GetCommandPool();
        auto& commandBuffer = currentFrame.GetCommandBuffer();

        commandBuffer.Reset();
        commandPool.Reset(VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);

        //Request image from the swapchain
        m_swapchainIndex = m_swapchain->AcquireNextImage(currentFrame.GetPresentSemaphore());

        //Begin the command buffer
        commandBuffer.Begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

        auto& framebuffer = m_swapchain->GetFramebuffer(m_swapchainIndex);

        const auto clearValue = Vulkan::Utils::ClearValueFromColor(clearColor);
        commandBuffer.BeginRenderPass(framebuffer, 1, &clearValue, VK_SUBPASS_CONTENTS_INLINE);

        return currentFrame;
    }

    void RenderFrameManager::EndFrame(Vulkan::Semaphore& waitSemaphore, VkPipelineStageFlags waitDstStageMask) {
        auto& currentFrame = GetCurrentFrame();

        auto& commandBuffer = currentFrame.GetCommandBuffer();

        commandBuffer.EndRenderPass();
        commandBuffer.End();

        auto& renderSemaphore = currentFrame.GetRenderSemaphore();
        auto& directQueue = m_device->GetDirectQueue();

        std::array<VkSemaphore, 2> waitSemaphores = { currentFrame.GetPresentSemaphore(), waitSemaphore };
        std::array<VkPipelineStageFlags, 2> waitDstStageMasks = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, waitDstStageMask};

        const auto submitInfo = Vulkan::Utils::SubmitInfo(static_cast<u32>(waitSemaphores.size()), waitSemaphores.data(), waitDstStageMasks.data(),
                                                        1, &commandBuffer.GetHandle(), 1, &renderSemaphore.GetHandle());

        directQueue.Submit(submitInfo, currentFrame.GetFrameFence());
        m_swapchain->Present(directQueue, renderSemaphore, m_swapchainIndex);

        //Set frame being rendered
        m_frameRenderMask.set(m_frameIndex, true);

        //Increment the frame index
        m_frameIndex = (++m_frameCounter % m_numFrameOverlaps);
    }

    void RenderFrameManager::AddFrameCompletionTask(std::function<void()> function) {
        KML_ASSERT(function);

        std::scoped_lock lock(m_mutex);
        m_frameCompletionTasks.emplace_back(m_frameRenderMask, std::move(function));
    }

    void RenderFrameManager::JoinFrameCompletionTasks() {
        m_device->WaitIdle();

        for(const auto& task : m_frameCompletionTasks) task.Function();
    }

    RenderFrameResources& RenderFrameManager::GetFrame(usize frameIndex) noexcept {
        KML_ASSERT(frameIndex < m_numFrameOverlaps);
        return m_resources[frameIndex];
    }

    const RenderFrameResources& RenderFrameManager::GetFrame(usize frameIndex) const noexcept {
        KML_ASSERT(frameIndex < m_numFrameOverlaps);
        return m_resources[frameIndex];
    }
}

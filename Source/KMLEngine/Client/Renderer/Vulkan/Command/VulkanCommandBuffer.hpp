//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanCommandBuffer.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_COMMAND_VULKANCOMMANDBUFFER_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_COMMAND_VULKANCOMMANDBUFFER_HPP

#pragma once

#include "../Util/VulkanObject.hpp"
#include "../../../../Common/Util/Math/Color4f.hpp"

namespace KMLEngine::Vulkan {
	class CommandPool;
    class Framebuffer;
	class CommandBuffer final : public DeviceObject<VkCommandBuffer, VK_OBJECT_TYPE_COMMAND_BUFFER>, public Disposable<CommandBuffer> {
		friend Disposable<CommandBuffer>;
	private:
		CommandPool* m_commandPool = nullptr;
		
		void OnDisposing();
	public:
		void Allocate(CommandPool& commandPool, VkCommandBufferLevel level);

		KML_FORCEINLINE void AllocatePrimary(CommandPool& commandPool) {
			Allocate(commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY);
		}

		KML_FORCEINLINE void AllocateSecondary(CommandPool& commandPool) {
			Allocate(commandPool, VK_COMMAND_BUFFER_LEVEL_SECONDARY);
		}

		KML_FORCEINLINE void Begin(const VkCommandBufferBeginInfo& commandBufferBeginInfo) {
			ThrowIfFailed(vkBeginCommandBuffer(m_handle, &commandBufferBeginInfo), "vkBeginCommandBuffer");
		}

		KML_FORCEINLINE void Begin(VkCommandBufferUsageFlags flags, const void* pNext = nullptr) { //TODO: move create info
			Begin(
				{
					.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
					.pNext = pNext,
					.flags = flags
				});
		}

		KML_FORCEINLINE void End() { ThrowIfFailed(vkEndCommandBuffer(m_handle), "vkEndCommandBuffer"); }

		KML_FORCEINLINE void Reset(VkCommandBufferResetFlags flags = 0) {
			ThrowIfFailed(vkResetCommandBuffer(m_handle, flags), "vkResetCommandBuffer");
		}

	    //Own functions
	    void BeginRenderPass(Framebuffer& framebuffer, u32 clearValueCount, const VkClearValue* pClearValues, VkSubpassContents contents) noexcept;

		void BeginDebugLabel(const char* name, const Color4f& color) noexcept;
		void EndDebugLabel();

		template<typename Pipeline>
		KML_FORCEINLINE void BindPipeline(Pipeline& pipeline) noexcept { BindPipeline(pipeline.GetBindPoint(), pipeline); }

		template<typename Pipeline, typename DescriptorSet>
		KML_FORCEINLINE void BindDescriptorSet(Pipeline& pipeline, DescriptorSet& descriptorSet, u32 firstSet = 0) {
            BindDescriptorSets(pipeline.GetBindPoint(), pipeline.GetLayout(), firstSet, 1, &descriptorSet.GetHandle(), 0, nullptr);
		}
		
		//Command Buffer functions
		KML_FORCEINLINE void BindPipeline(VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) noexcept {
			vkCmdBindPipeline(m_handle, pipelineBindPoint, pipeline);
		}
		
		KML_FORCEINLINE void SetViewport(u32 firstViewport, u32 viewportCount, const VkViewport* viewports) noexcept {
			vkCmdSetViewport(m_handle, firstViewport, viewportCount, viewports);
		}
		
		KML_FORCEINLINE void SetScissor(u32 firstScissor, u32 scissorCount, const VkRect2D* scissors) noexcept {
			vkCmdSetScissor(m_handle, firstScissor, scissorCount, scissors);
		}
		
		KML_FORCEINLINE void SetLineWidth(f32 lineWidth) noexcept {
			vkCmdSetLineWidth(m_handle, lineWidth);
		}
		
		KML_FORCEINLINE void SetDepthBias(f32 depthBiasConstantFactor, f32 depthBiasClamp, f32 depthBiasSlopeFactor) noexcept {
			vkCmdSetDepthBias(m_handle, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
		}
		
		KML_FORCEINLINE void SetBlendConstants(const f32 blendConstants[4]) noexcept {
			vkCmdSetBlendConstants(m_handle, blendConstants);
		}
		
		KML_FORCEINLINE void SetDepthBounds(f32 minDepthBounds, f32 maxDepthBounds) noexcept {
			vkCmdSetDepthBounds(m_handle, minDepthBounds, maxDepthBounds);
		}
		
		KML_FORCEINLINE void SetStencilCompareMask(VkStencilFaceFlags faceMask, u32 compareMask) noexcept {
			vkCmdSetStencilCompareMask(m_handle, faceMask, compareMask);
		}
		
		KML_FORCEINLINE void SetStencilWriteMask(VkStencilFaceFlags faceMask, u32 writeMask) noexcept {
			vkCmdSetStencilWriteMask(m_handle, faceMask, writeMask);
		}
		
		KML_FORCEINLINE void SetStencilReference(VkStencilFaceFlags faceMask, u32 reference) noexcept {
			vkCmdSetStencilReference(m_handle, faceMask, reference);
		}
		
		KML_FORCEINLINE void BindDescriptorSets(VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, u32 firstSet, u32 descriptorSetCount, const VkDescriptorSet* descriptorSets, u32 dynamicOffsetCount, const u32* dynamicOffsets) noexcept {
			vkCmdBindDescriptorSets(m_handle, pipelineBindPoint, layout, firstSet, descriptorSetCount, descriptorSets, dynamicOffsetCount, dynamicOffsets);
		}
		
		KML_FORCEINLINE void BindIndexBuffer(VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) noexcept {
			vkCmdBindIndexBuffer(m_handle, buffer, offset, indexType);
		}
		
		KML_FORCEINLINE void BindVertexBuffers(u32 firstBinding, u32 bindingCount, const VkBuffer* buffers, const VkDeviceSize* offsets) noexcept {
			vkCmdBindVertexBuffers(m_handle, firstBinding, bindingCount, buffers, offsets);
		}
		
		KML_FORCEINLINE void Draw(u32 vertexCount, u32 instanceCount, u32 firstVertex, u32 firstInstance) noexcept {
			vkCmdDraw(m_handle, vertexCount, instanceCount, firstVertex, firstInstance);
		}
		
		KML_FORCEINLINE void DrawIndexed(u32 indexCount, u32 instanceCount, u32 firstIndex, i32 vertexOffset, u32 firstInstance) noexcept {
			vkCmdDrawIndexed(m_handle, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
		}
		
		KML_FORCEINLINE void DrawIndirect(VkBuffer buffer, VkDeviceSize offset, u32 drawCount, u32 stride) noexcept {
			vkCmdDrawIndirect(m_handle, buffer, offset, drawCount, stride);
		}
		
		KML_FORCEINLINE void DrawIndexedIndirect(VkBuffer buffer, VkDeviceSize offset, u32 drawCount, u32 stride) noexcept {
			vkCmdDrawIndexedIndirect(m_handle, buffer, offset, drawCount, stride);
		}
		
		KML_FORCEINLINE void Dispatch(u32 groupCountX, u32 groupCountY, u32 groupCountZ) noexcept {
			vkCmdDispatch(m_handle, groupCountX, groupCountY, groupCountZ);
		}
		
		KML_FORCEINLINE void DispatchIndirect(VkBuffer buffer, VkDeviceSize offset) noexcept {
			vkCmdDispatchIndirect(m_handle, buffer, offset);
		}
		
		KML_FORCEINLINE void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, u32 regionCount, const VkBufferCopy* regions) noexcept {
			vkCmdCopyBuffer(m_handle, srcBuffer, dstBuffer, regionCount, regions);
		}
		
		KML_FORCEINLINE void CopyImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, u32 regionCount, const VkImageCopy* regions) noexcept {
			vkCmdCopyImage(m_handle, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, regions);
		}
		
		KML_FORCEINLINE void BlitImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, u32 regionCount, const VkImageBlit* regions, VkFilter filter) noexcept {
			vkCmdBlitImage(m_handle, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, regions, filter);
		}
		
		KML_FORCEINLINE void CopyBufferToImage(VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, u32 regionCount, const VkBufferImageCopy* regions) noexcept {
			vkCmdCopyBufferToImage(m_handle, srcBuffer, dstImage, dstImageLayout, regionCount, regions);
		}
		
		KML_FORCEINLINE void CopyImageToBuffer(VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, u32 regionCount, const VkBufferImageCopy* regions) noexcept {
			vkCmdCopyImageToBuffer(m_handle, srcImage, srcImageLayout, dstBuffer, regionCount, regions);
		}
		
		KML_FORCEINLINE void UpdateBuffer(VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* data) noexcept {
			vkCmdUpdateBuffer(m_handle, dstBuffer, dstOffset, dataSize, data);
		}
		
		KML_FORCEINLINE void FillBuffer(VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, u32 data) noexcept {
			vkCmdFillBuffer(m_handle, dstBuffer, dstOffset, size, data);
		}
		
		KML_FORCEINLINE void ClearColorImage(VkImage image, VkImageLayout imageLayout, const VkClearColorValue* color, u32 rangeCount, const VkImageSubresourceRange* ranges) noexcept {
			vkCmdClearColorImage(m_handle, image, imageLayout, color, rangeCount, ranges);
		}
		
		KML_FORCEINLINE void ClearDepthStencilImage(VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* depthStencil, u32 rangeCount, const VkImageSubresourceRange* ranges) noexcept {
			vkCmdClearDepthStencilImage(m_handle, image, imageLayout, depthStencil, rangeCount, ranges);
		}
		
		KML_FORCEINLINE void ClearAttachments(u32 attachmentCount, const VkClearAttachment* attachments, u32 rectCount, const VkClearRect* rects) noexcept {
			vkCmdClearAttachments(m_handle, attachmentCount, attachments, rectCount, rects);
		}
		
		KML_FORCEINLINE void ResolveImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, u32 regionCount, const VkImageResolve* regions) noexcept {
			vkCmdResolveImage(m_handle, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, regions);
		}
		
		KML_FORCEINLINE void SetEvent(VkEvent event, VkPipelineStageFlags stageMask) noexcept {
			vkCmdSetEvent(m_handle, event, stageMask);
		}
		
		KML_FORCEINLINE void ResetEvent(VkEvent event, VkPipelineStageFlags stageMask) noexcept {
			vkCmdResetEvent(m_handle, event, stageMask);
		}
		
		KML_FORCEINLINE void WaitEvents(u32 eventCount, const VkEvent* events, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, u32 memoryBarrierCount, const VkMemoryBarrier* memoryBarriers, u32 bufferMemoryBarrierCount, const VkBufferMemoryBarrier* bufferMemoryBarriers, u32 imageMemoryBarrierCount, const VkImageMemoryBarrier* imageMemoryBarriers) noexcept {
			vkCmdWaitEvents(m_handle, eventCount, events, srcStageMask, dstStageMask, memoryBarrierCount, memoryBarriers, bufferMemoryBarrierCount, bufferMemoryBarriers, imageMemoryBarrierCount, imageMemoryBarriers);
		}
		
		KML_FORCEINLINE void PipelineBarrier(VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, u32 memoryBarrierCount, const VkMemoryBarrier* memoryBarriers, u32 bufferMemoryBarrierCount, const VkBufferMemoryBarrier* bufferMemoryBarriers, u32 imageMemoryBarrierCount, const VkImageMemoryBarrier* imageMemoryBarriers) noexcept {
			vkCmdPipelineBarrier(m_handle, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, memoryBarriers, bufferMemoryBarrierCount, bufferMemoryBarriers, imageMemoryBarrierCount, imageMemoryBarriers);
		}
		
		KML_FORCEINLINE void BeginQuery(VkQueryPool queryPool, u32 query, VkQueryControlFlags flags) noexcept {
			vkCmdBeginQuery(m_handle, queryPool, query, flags);
		}
		
		KML_FORCEINLINE void EndQuery(VkQueryPool queryPool, u32 query) noexcept {
			vkCmdEndQuery(m_handle, queryPool, query);
		}
		
		KML_FORCEINLINE void BeginConditionalRenderingEXT(const VkConditionalRenderingBeginInfoEXT* conditionalRenderingBegin) noexcept {
			vkCmdBeginConditionalRenderingEXT(m_handle, conditionalRenderingBegin);
		}
		
		KML_FORCEINLINE void EndConditionalRenderingEXT() noexcept {
			vkCmdEndConditionalRenderingEXT(m_handle);
		}
		
		KML_FORCEINLINE void ResetQueryPool(VkQueryPool queryPool, u32 firstQuery, u32 queryCount) noexcept {
			vkCmdResetQueryPool(m_handle, queryPool, firstQuery, queryCount);
		}
		
		KML_FORCEINLINE void WriteTimestamp(VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, u32 query) noexcept {
			vkCmdWriteTimestamp(m_handle, pipelineStage, queryPool, query);
		}
		
		KML_FORCEINLINE void CopyQueryPoolResults(VkQueryPool queryPool, u32 firstQuery, u32 queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) noexcept {
			vkCmdCopyQueryPoolResults(m_handle, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
		}
		
		KML_FORCEINLINE void PushConstants(VkPipelineLayout layout, VkShaderStageFlags stageFlags, u32 offset, u32 size, const void* values) noexcept {
			vkCmdPushConstants(m_handle, layout, stageFlags, offset, size, values);
		}
		
		KML_FORCEINLINE void BeginRenderPass(const VkRenderPassBeginInfo* renderPassBegin, VkSubpassContents contents) noexcept {
			vkCmdBeginRenderPass(m_handle, renderPassBegin, contents);
		}
		
		KML_FORCEINLINE void NextSubpass(VkSubpassContents contents) noexcept {
			vkCmdNextSubpass(m_handle, contents);
		}
		
		KML_FORCEINLINE void EndRenderPass() noexcept {
			vkCmdEndRenderPass(m_handle);
		}
		
		KML_FORCEINLINE void ExecuteCommands(u32 commandBufferCount, const VkCommandBuffer* commandBuffers) noexcept {
			vkCmdExecuteCommands(m_handle, commandBufferCount, commandBuffers);
		}
		
		KML_FORCEINLINE void DebugMarkerBeginEXT(const VkDebugMarkerMarkerInfoEXT* markerInfo) noexcept {
			vkCmdDebugMarkerBeginEXT(m_handle, markerInfo);
		}
		
		KML_FORCEINLINE void DebugMarkerEndEXT() noexcept {
			vkCmdDebugMarkerEndEXT(m_handle);
		}
		
		KML_FORCEINLINE void DebugMarkerInsertEXT(const VkDebugMarkerMarkerInfoEXT* markerInfo) noexcept {
			vkCmdDebugMarkerInsertEXT(m_handle, markerInfo);
		}
		
		KML_FORCEINLINE void ExecuteGeneratedCommandsNV(VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* generatedCommandsInfo) noexcept {
			vkCmdExecuteGeneratedCommandsNV(m_handle, isPreprocessed, generatedCommandsInfo);
		}
		
		KML_FORCEINLINE void PreprocessGeneratedCommandsNV(const VkGeneratedCommandsInfoNV* generatedCommandsInfo) noexcept {
			vkCmdPreprocessGeneratedCommandsNV(m_handle, generatedCommandsInfo);
		}
		
		KML_FORCEINLINE void BindPipelineShaderGroupNV(VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, u32 groupIndex) noexcept {
			vkCmdBindPipelineShaderGroupNV(m_handle, pipelineBindPoint, pipeline, groupIndex);
		}
		
		KML_FORCEINLINE void PushDescriptorSetKHR(VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, u32 set, u32 descriptorWriteCount, const VkWriteDescriptorSet* descriptorWrites) noexcept {
			vkCmdPushDescriptorSetKHR(m_handle, pipelineBindPoint, layout, set, descriptorWriteCount, descriptorWrites);
		}
		
		KML_FORCEINLINE void SetDeviceMask(u32 deviceMask) noexcept {
			vkCmdSetDeviceMask(m_handle, deviceMask);
		}
		
		KML_FORCEINLINE void DispatchBase(u32 baseGroupX, u32 baseGroupY, u32 baseGroupZ, u32 groupCountX, u32 groupCountY, u32 groupCountZ) noexcept {
			vkCmdDispatchBase(m_handle, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
		}
		
		KML_FORCEINLINE void PushDescriptorSetWithTemplateKHR(VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, u32 set, const void* data) noexcept {
			vkCmdPushDescriptorSetWithTemplateKHR(m_handle, descriptorUpdateTemplate, layout, set, data);
		}
		
		KML_FORCEINLINE void SetViewportWScalingNV(u32 firstViewport, u32 viewportCount, const VkViewportWScalingNV* viewportWScalings) noexcept {
			vkCmdSetViewportWScalingNV(m_handle, firstViewport, viewportCount, viewportWScalings);
		}
		
		KML_FORCEINLINE void SetDiscardRectangleEXT(u32 firstDiscardRectangle, u32 discardRectangleCount, const VkRect2D* discardRectangles) noexcept {
			vkCmdSetDiscardRectangleEXT(m_handle, firstDiscardRectangle, discardRectangleCount, discardRectangles);
		}
		
		KML_FORCEINLINE void SetSampleLocationsEXT(const VkSampleLocationsInfoEXT* sampleLocationsInfo) noexcept {
			vkCmdSetSampleLocationsEXT(m_handle, sampleLocationsInfo);
		}
		
		KML_FORCEINLINE void BeginDebugUtilsLabelEXT(const VkDebugUtilsLabelEXT* labelInfo) noexcept {
			vkCmdBeginDebugUtilsLabelEXT(m_handle, labelInfo);
		}
		
		KML_FORCEINLINE void EndDebugUtilsLabelEXT() noexcept {
			vkCmdEndDebugUtilsLabelEXT(m_handle);
		}
		
		KML_FORCEINLINE void InsertDebugUtilsLabelEXT(const VkDebugUtilsLabelEXT* labelInfo) noexcept {
			vkCmdInsertDebugUtilsLabelEXT(m_handle, labelInfo);
		}
		
		KML_FORCEINLINE void WriteBufferMarkerAMD(VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, u32 marker) noexcept {
			vkCmdWriteBufferMarkerAMD(m_handle, pipelineStage, dstBuffer, dstOffset, marker);
		}
		
		KML_FORCEINLINE void BeginRenderPass2(const VkRenderPassBeginInfo* renderPassBegin, const VkSubpassBeginInfo* subpassBeginInfo) noexcept {
			vkCmdBeginRenderPass2(m_handle, renderPassBegin, subpassBeginInfo);
		}
		
		KML_FORCEINLINE void NextSubpass2(const VkSubpassBeginInfo* subpassBeginInfo, const VkSubpassEndInfo* subpassEndInfo) noexcept {
			vkCmdNextSubpass2(m_handle, subpassBeginInfo, subpassEndInfo);
		}
		
		KML_FORCEINLINE void EndRenderPass2(const VkSubpassEndInfo* subpassEndInfo) noexcept {
			vkCmdEndRenderPass2(m_handle, subpassEndInfo);
		}
		
		KML_FORCEINLINE void DrawIndirectCount(VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, u32 maxDrawCount, u32 stride) noexcept {
			vkCmdDrawIndirectCount(m_handle, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
		}
		
		KML_FORCEINLINE void DrawIndexedIndirectCount(VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, u32 maxDrawCount, u32 stride) noexcept {
			vkCmdDrawIndexedIndirectCount(m_handle, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
		}
		
		KML_FORCEINLINE void SetCheckpointNV(const void* checkpointMarker) noexcept {
			vkCmdSetCheckpointNV(m_handle, checkpointMarker);
		}
		
		KML_FORCEINLINE void BindTransformFeedbackBuffersEXT(u32 firstBinding, u32 bindingCount, const VkBuffer* buffers, const VkDeviceSize* offsets, const VkDeviceSize* sizes) noexcept {
			vkCmdBindTransformFeedbackBuffersEXT(m_handle, firstBinding, bindingCount, buffers, offsets, sizes);
		}
		
		KML_FORCEINLINE void BeginTransformFeedbackEXT(u32 firstCounterBuffer, u32 counterBufferCount, const VkBuffer* counterBuffers, const VkDeviceSize* counterBufferOffsets) noexcept {
			vkCmdBeginTransformFeedbackEXT(m_handle, firstCounterBuffer, counterBufferCount, counterBuffers, counterBufferOffsets);
		}
		
		KML_FORCEINLINE void EndTransformFeedbackEXT(u32 firstCounterBuffer, u32 counterBufferCount, const VkBuffer* counterBuffers, const VkDeviceSize* counterBufferOffsets) noexcept {
			vkCmdEndTransformFeedbackEXT(m_handle, firstCounterBuffer, counterBufferCount, counterBuffers, counterBufferOffsets);
		}
		
		KML_FORCEINLINE void BeginQueryIndexedEXT(VkQueryPool queryPool, u32 query, VkQueryControlFlags flags, u32 index) noexcept {
			vkCmdBeginQueryIndexedEXT(m_handle, queryPool, query, flags, index);
		}
		
		KML_FORCEINLINE void EndQueryIndexedEXT(VkQueryPool queryPool, u32 query, u32 index) noexcept {
			vkCmdEndQueryIndexedEXT(m_handle, queryPool, query, index);
		}
		
		KML_FORCEINLINE void DrawIndirectByteCountEXT(u32 instanceCount, u32 firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, u32 counterOffset, u32 vertexStride) noexcept {
			vkCmdDrawIndirectByteCountEXT(m_handle, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride);
		}
		
		KML_FORCEINLINE void SetExclusiveScissorNV(u32 firstExclusiveScissor, u32 exclusiveScissorCount, const VkRect2D* exclusiveScissors) noexcept {
			vkCmdSetExclusiveScissorNV(m_handle, firstExclusiveScissor, exclusiveScissorCount, exclusiveScissors);
		}
		
		KML_FORCEINLINE void BindShadingRateImageNV(VkImageView imageView, VkImageLayout imageLayout) noexcept {
			vkCmdBindShadingRateImageNV(m_handle, imageView, imageLayout);
		}
		
		KML_FORCEINLINE void SetViewportShadingRatePaletteNV(u32 firstViewport, u32 viewportCount, const VkShadingRatePaletteNV* shadingRatePalettes) noexcept {
			vkCmdSetViewportShadingRatePaletteNV(m_handle, firstViewport, viewportCount, shadingRatePalettes);
		}
		
		KML_FORCEINLINE void SetCoarseSampleOrderNV(VkCoarseSampleOrderTypeNV sampleOrderType, u32 customSampleOrderCount, const VkCoarseSampleOrderCustomNV* customSampleOrders) noexcept {
			vkCmdSetCoarseSampleOrderNV(m_handle, sampleOrderType, customSampleOrderCount, customSampleOrders);
		}
		
		KML_FORCEINLINE void DrawMeshTasksNV(u32 taskCount, u32 firstTask) noexcept {
			vkCmdDrawMeshTasksNV(m_handle, taskCount, firstTask);
		}
		
		KML_FORCEINLINE void DrawMeshTasksIndirectNV(VkBuffer buffer, VkDeviceSize offset, u32 drawCount, u32 stride) noexcept {
			vkCmdDrawMeshTasksIndirectNV(m_handle, buffer, offset, drawCount, stride);
		}
		
		KML_FORCEINLINE void DrawMeshTasksIndirectCountNV(VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, u32 maxDrawCount, u32 stride) noexcept {
			vkCmdDrawMeshTasksIndirectCountNV(m_handle, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
		}
		
		KML_FORCEINLINE void CopyAccelerationStructureNV(VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeKHR mode) noexcept {
			vkCmdCopyAccelerationStructureNV(m_handle, dst, src, mode);
		}
		
		KML_FORCEINLINE void CopyAccelerationStructureKHR(const VkCopyAccelerationStructureInfoKHR* info) noexcept {
			vkCmdCopyAccelerationStructureKHR(m_handle, info);
		}
		
		KML_FORCEINLINE void CopyAccelerationStructureToMemoryKHR(const VkCopyAccelerationStructureToMemoryInfoKHR* info) noexcept {
			vkCmdCopyAccelerationStructureToMemoryKHR(m_handle, info);
		}
		
		KML_FORCEINLINE void CopyMemoryToAccelerationStructureKHR(const VkCopyMemoryToAccelerationStructureInfoKHR* info) noexcept {
			vkCmdCopyMemoryToAccelerationStructureKHR(m_handle, info);
		}
		
		KML_FORCEINLINE void WriteAccelerationStructuresPropertiesKHR(u32 accelerationStructureCount, const VkAccelerationStructureKHR* accelerationStructures, VkQueryType queryType, VkQueryPool queryPool, u32 firstQuery) noexcept {
			vkCmdWriteAccelerationStructuresPropertiesKHR(m_handle, accelerationStructureCount, accelerationStructures, queryType, queryPool, firstQuery);
		}
		
		KML_FORCEINLINE void WriteAccelerationStructuresPropertiesNV(u32 accelerationStructureCount, const VkAccelerationStructureNV* accelerationStructures, VkQueryType queryType, VkQueryPool queryPool, u32 firstQuery) noexcept {
			vkCmdWriteAccelerationStructuresPropertiesNV(m_handle, accelerationStructureCount, accelerationStructures, queryType, queryPool, firstQuery);
		}
		
		KML_FORCEINLINE void BuildAccelerationStructureNV(const VkAccelerationStructureInfoNV* info, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset) noexcept {
			vkCmdBuildAccelerationStructureNV(m_handle, info, instanceData, instanceOffset, update, dst, src, scratch, scratchOffset);
		}
		
		KML_FORCEINLINE void TraceRaysKHR(const VkStridedDeviceAddressRegionKHR* raygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* missShaderBindingTable, const VkStridedDeviceAddressRegionKHR* hitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* callableShaderBindingTable, u32 width, u32 height, u32 depth) noexcept {
			vkCmdTraceRaysKHR(m_handle, raygenShaderBindingTable, missShaderBindingTable, hitShaderBindingTable, callableShaderBindingTable, width, height, depth);
		}
		
		KML_FORCEINLINE void TraceRaysNV(VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, u32 width, u32 height, u32 depth) noexcept {
			vkCmdTraceRaysNV(m_handle, raygenShaderBindingTableBuffer, raygenShaderBindingOffset, missShaderBindingTableBuffer, missShaderBindingOffset, missShaderBindingStride, hitShaderBindingTableBuffer, hitShaderBindingOffset, hitShaderBindingStride, callableShaderBindingTableBuffer, callableShaderBindingOffset, callableShaderBindingStride, width, height, depth);
		}
		
		KML_FORCEINLINE void TraceRaysIndirectKHR(const VkStridedDeviceAddressRegionKHR* raygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* missShaderBindingTable, const VkStridedDeviceAddressRegionKHR* hitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* callableShaderBindingTable, VkDeviceAddress indirectDeviceAddress) noexcept {
			vkCmdTraceRaysIndirectKHR(m_handle, raygenShaderBindingTable, missShaderBindingTable, hitShaderBindingTable, callableShaderBindingTable, indirectDeviceAddress);
		}
		
		KML_FORCEINLINE void SetRayTracingPipelineStackSizeKHR(u32 pipelineStackSize) noexcept {
			vkCmdSetRayTracingPipelineStackSizeKHR(m_handle, pipelineStackSize);
		}
		
		KML_FORCEINLINE VkResult SetPerformanceMarkerINTEL(const VkPerformanceMarkerInfoINTEL* markerInfo) noexcept {
			return vkCmdSetPerformanceMarkerINTEL(m_handle, markerInfo);
		}
		
		KML_FORCEINLINE VkResult SetPerformanceStreamMarkerINTEL(const VkPerformanceStreamMarkerInfoINTEL* markerInfo) noexcept {
			return vkCmdSetPerformanceStreamMarkerINTEL(m_handle, markerInfo);
		}
		
		KML_FORCEINLINE VkResult SetPerformanceOverrideINTEL(const VkPerformanceOverrideInfoINTEL* overrideInfo) noexcept {
			return vkCmdSetPerformanceOverrideINTEL(m_handle, overrideInfo);
		}
		
		KML_FORCEINLINE void SetLineStippleEXT(u32 lineStippleFactor, u16 lineStipplePattern) noexcept {
			vkCmdSetLineStippleEXT(m_handle, lineStippleFactor, lineStipplePattern);
		}
		
		KML_FORCEINLINE void BuildAccelerationStructuresKHR(u32 infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* infos, const VkAccelerationStructureBuildRangeInfoKHR* const* buildRangeInfos) noexcept {
			vkCmdBuildAccelerationStructuresKHR(m_handle, infoCount, infos, buildRangeInfos);
		}
		
		KML_FORCEINLINE void BuildAccelerationStructuresIndirectKHR(u32 infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* infos, const VkDeviceAddress* indirectDeviceAddresses, const u32* indirectStrides, const u32* const* maxPrimitiveCounts) noexcept {
			vkCmdBuildAccelerationStructuresIndirectKHR(m_handle, infoCount, infos, indirectDeviceAddresses, indirectStrides, maxPrimitiveCounts);
		}
		
		KML_FORCEINLINE void SetCullModeEXT(VkCullModeFlags cullMode) noexcept {
			vkCmdSetCullModeEXT(m_handle, cullMode);
		}
		
		KML_FORCEINLINE void SetFrontFaceEXT(VkFrontFace frontFace) noexcept {
			vkCmdSetFrontFaceEXT(m_handle, frontFace);
		}
		
		KML_FORCEINLINE void SetPrimitiveTopologyEXT(VkPrimitiveTopology primitiveTopology) noexcept {
			vkCmdSetPrimitiveTopologyEXT(m_handle, primitiveTopology);
		}
		
		KML_FORCEINLINE void SetViewportWithCountEXT(u32 viewportCount, const VkViewport* viewports) noexcept {
			vkCmdSetViewportWithCountEXT(m_handle, viewportCount, viewports);
		}
		
		KML_FORCEINLINE void SetScissorWithCountEXT(u32 scissorCount, const VkRect2D* scissors) noexcept {
			vkCmdSetScissorWithCountEXT(m_handle, scissorCount, scissors);
		}
		
		KML_FORCEINLINE void BindVertexBuffers2EXT(u32 firstBinding, u32 bindingCount, const VkBuffer* buffers, const VkDeviceSize* offsets, const VkDeviceSize* sizes, const VkDeviceSize* strides) noexcept {
			vkCmdBindVertexBuffers2EXT(m_handle, firstBinding, bindingCount, buffers, offsets, sizes, strides);
		}
		
		KML_FORCEINLINE void SetDepthTestEnableEXT(VkBool32 depthTestEnable) noexcept {
			vkCmdSetDepthTestEnableEXT(m_handle, depthTestEnable);
		}
		
		KML_FORCEINLINE void SetDepthWriteEnableEXT(VkBool32 depthWriteEnable) noexcept {
			vkCmdSetDepthWriteEnableEXT(m_handle, depthWriteEnable);
		}
		
		KML_FORCEINLINE void SetDepthCompareOpEXT(VkCompareOp depthCompareOp) noexcept {
			vkCmdSetDepthCompareOpEXT(m_handle, depthCompareOp);
		}
		
		KML_FORCEINLINE void SetDepthBoundsTestEnableEXT(VkBool32 depthBoundsTestEnable) noexcept {
			vkCmdSetDepthBoundsTestEnableEXT(m_handle, depthBoundsTestEnable);
		}
		
		KML_FORCEINLINE void SetStencilTestEnableEXT(VkBool32 stencilTestEnable) noexcept {
			vkCmdSetStencilTestEnableEXT(m_handle, stencilTestEnable);
		}
		
		KML_FORCEINLINE void SetStencilOpEXT(VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) noexcept {
			vkCmdSetStencilOpEXT(m_handle, faceMask, failOp, passOp, depthFailOp, compareOp);
		}
		
		KML_FORCEINLINE void SetPatchControlPointsEXT(u32 patchControlPoints) noexcept {
			vkCmdSetPatchControlPointsEXT(m_handle, patchControlPoints);
		}
		
		KML_FORCEINLINE void SetRasterizerDiscardEnableEXT(VkBool32 rasterizerDiscardEnable) noexcept {
			vkCmdSetRasterizerDiscardEnableEXT(m_handle, rasterizerDiscardEnable);
		}
		
		KML_FORCEINLINE void SetDepthBiasEnableEXT(VkBool32 depthBiasEnable) noexcept {
			vkCmdSetDepthBiasEnableEXT(m_handle, depthBiasEnable);
		}
		
		KML_FORCEINLINE void SetLogicOpEXT(VkLogicOp logicOp) noexcept {
			vkCmdSetLogicOpEXT(m_handle, logicOp);
		}
		
		KML_FORCEINLINE void SetPrimitiveRestartEnableEXT(VkBool32 primitiveRestartEnable) noexcept {
			vkCmdSetPrimitiveRestartEnableEXT(m_handle, primitiveRestartEnable);
		}
		
		KML_FORCEINLINE void CopyBuffer2KHR(const VkCopyBufferInfo2KHR* copyBufferInfo) noexcept {
			vkCmdCopyBuffer2KHR(m_handle, copyBufferInfo);
		}
		
		KML_FORCEINLINE void CopyImage2KHR(const VkCopyImageInfo2KHR* copyImageInfo) noexcept {
			vkCmdCopyImage2KHR(m_handle, copyImageInfo);
		}
		
		KML_FORCEINLINE void BlitImage2KHR(const VkBlitImageInfo2KHR* blitImageInfo) noexcept {
			vkCmdBlitImage2KHR(m_handle, blitImageInfo);
		}
		
		KML_FORCEINLINE void CopyBufferToImage2KHR(const VkCopyBufferToImageInfo2KHR* copyBufferToImageInfo) noexcept {
			vkCmdCopyBufferToImage2KHR(m_handle, copyBufferToImageInfo);
		}
		
		KML_FORCEINLINE void CopyImageToBuffer2KHR(const VkCopyImageToBufferInfo2KHR* copyImageToBufferInfo) noexcept {
			vkCmdCopyImageToBuffer2KHR(m_handle, copyImageToBufferInfo);
		}
		
		KML_FORCEINLINE void ResolveImage2KHR(const VkResolveImageInfo2KHR* resolveImageInfo) noexcept {
			vkCmdResolveImage2KHR(m_handle, resolveImageInfo);
		}
		
		KML_FORCEINLINE void SetFragmentShadingRateKHR(const VkExtent2D* fragmentSize, const VkFragmentShadingRateCombinerOpKHR combinerOps[2]) noexcept {
			vkCmdSetFragmentShadingRateKHR(m_handle, fragmentSize, combinerOps);
		}
		
		KML_FORCEINLINE void SetFragmentShadingRateEnumNV(VkFragmentShadingRateNV shadingRate, const VkFragmentShadingRateCombinerOpKHR combinerOps[2]) noexcept {
			vkCmdSetFragmentShadingRateEnumNV(m_handle, shadingRate, combinerOps);
		}
		
		KML_FORCEINLINE void SetVertexInputEXT(u32 vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* vertexBindingDescriptions, u32 vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* vertexAttributeDescriptions) noexcept {
			vkCmdSetVertexInputEXT(m_handle, vertexBindingDescriptionCount, vertexBindingDescriptions, vertexAttributeDescriptionCount, vertexAttributeDescriptions);
		}
		
		KML_FORCEINLINE void SetColorWriteEnableEXT(u32 attachmentCount, const VkBool32* colorWriteEnables) noexcept {
			vkCmdSetColorWriteEnableEXT(m_handle, attachmentCount, colorWriteEnables);
		}
		
		KML_FORCEINLINE void SetEvent2KHR(VkEvent event, const VkDependencyInfoKHR* dependencyInfo) noexcept {
			vkCmdSetEvent2KHR(m_handle, event, dependencyInfo);
		}
		
		KML_FORCEINLINE void ResetEvent2KHR(VkEvent event, VkPipelineStageFlags2KHR stageMask) noexcept {
			vkCmdResetEvent2KHR(m_handle, event, stageMask);
		}
		
		KML_FORCEINLINE void WaitEvents2KHR(u32 eventCount, const VkEvent* events, const VkDependencyInfoKHR* dependencyInfos) noexcept {
			vkCmdWaitEvents2KHR(m_handle, eventCount, events, dependencyInfos);
		}
		
		KML_FORCEINLINE void PipelineBarrier2KHR(const VkDependencyInfoKHR* dependencyInfo) noexcept {
			vkCmdPipelineBarrier2KHR(m_handle, dependencyInfo);
		}
		
		KML_FORCEINLINE void WriteTimestamp2KHR(VkPipelineStageFlags2KHR stage, VkQueryPool queryPool, u32 query) noexcept {
			vkCmdWriteTimestamp2KHR(m_handle, stage, queryPool, query);
		}
		
		KML_FORCEINLINE void WriteBufferMarker2AMD(VkPipelineStageFlags2KHR stage, VkBuffer dstBuffer, VkDeviceSize dstOffset, u32 marker) noexcept {
			vkCmdWriteBufferMarker2AMD(m_handle, stage, dstBuffer, dstOffset, marker);
		}
		
		/*TODO: KML_FORCEINLINE void DecodeVideoKHR(const VkVideoDecodeInfoKHR* frameInfo) noexcept {
			vkCmdDecodeVideoKHR(m_handle, frameInfo);
		}
		
		KML_FORCEINLINE void BeginVideoCodingKHR(const VkVideoBeginCodingInfoKHR* beginInfo) noexcept {
			vkCmdBeginVideoCodingKHR(m_handle, beginInfo);
		}
		
		KML_FORCEINLINE void ControlVideoCodingKHR(const VkVideoCodingControlInfoKHR* codingControlInfo) noexcept {
			vkCmdControlVideoCodingKHR(m_handle, codingControlInfo);
		}
		
		KML_FORCEINLINE void EndVideoCodingKHR(const VkVideoEndCodingInfoKHR* endCodingInfo) noexcept {
			vkCmdEndVideoCodingKHR(m_handle, endCodingInfo);
		}
		
		KML_FORCEINLINE void EncodeVideoKHR(const VkVideoEncodeInfoKHR* encodeInfo) noexcept {
			vkCmdEncodeVideoKHR(m_handle, encodeInfo);
		}*/

		//Getters
		[[nodiscard]] KML_FORCEINLINE CommandPool& GetCommandPool() noexcept {
			KML_ASSERT(m_commandPool);
			return *m_commandPool;
		}

		[[nodiscard]] KML_FORCEINLINE const CommandPool& GetCommandPool() const noexcept {
			KML_ASSERT(m_commandPool);
			return *m_commandPool;
		}
	};
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_COMMAND_VULKANCOMMANDBUFFER_HPP
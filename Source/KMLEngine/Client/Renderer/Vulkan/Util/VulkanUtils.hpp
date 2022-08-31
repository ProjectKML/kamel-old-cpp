//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanUtils.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_VULKANUTILS_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_VULKANUTILS_HPP

#pragma once

#include "Vulkan.hpp"
#include "../../../../Common/Util/Math/Color4f.hpp"
#include "../../../../Common/Util/Math/Point.hpp"
#include "../../../../Platform/Hints/ForceInline.hpp"

namespace KMLEngine::Vulkan::Utils {
	KML_FORCEINLINE VkViewport Viewport(f32 x, f32 y, f32 width, f32 height, f32 minDepth = 0.0f, f32 maxDepth = 1.0f) noexcept {
		return {
			.x = x,
			.y = y,
			.width = width,
			.height = height,
			.minDepth = minDepth,
			.maxDepth = maxDepth
		};
	}

	KML_FORCEINLINE VkOffset2D Offset2D(i32 x, i32 y) noexcept {
		return {
			.x = x,
			.y = y
		};
	}

	KML_FORCEINLINE VkOffset3D Offset3D(i32 x, i32 y, i32 z) noexcept {
		return {
			.x = x,
			.y = y,
			.z = z
		};
	}

	KML_FORCEINLINE VkExtent2D Extent2D(u32 width, u32 height) noexcept {
		return {
			.width = width,
			.height = height
		};
	}

	KML_FORCEINLINE VkExtent3D Extent3D(u32 width, u32 height, u32 depth) noexcept {
		return {
			.width = width,
			.height = height,
			.depth = depth
		};
	}

	KML_FORCEINLINE VkRect2D Rect2D(i32 x, i32 y, u32 width, u32 height) noexcept {
		return {
			.offset = Offset2D(x, y),
			.extent = Extent2D(width, height)
		};
	}

	//Image
	KML_FORCEINLINE VkImageSubresourceRange ImageSubresourceRange(VkImageAspectFlags aspectMask, u32 baseMipLevel = 0, u32 levelCount = 1, u32 baseArrayLayer = 0,
	                                                              u32 layerCount = 1) noexcept {
		return {
			.aspectMask = aspectMask,
			.baseMipLevel = baseMipLevel,
			.levelCount = levelCount,
			.baseArrayLayer = baseArrayLayer,
			.layerCount = layerCount
		};
	}

	KML_FORCEINLINE VkImageSubresourceLayers ImageSubresourceLayers(VkImageAspectFlags aspectMask, u32 mipLevel, u32 baseArrayLayer, u32 layerCount) {
		return {
			.aspectMask = aspectMask,
			.mipLevel = mipLevel,
			.baseArrayLayer = baseArrayLayer,
			.layerCount = layerCount
		};
	}

	//Main
	KML_FORCEINLINE VkApplicationInfo ApplicationInfo(const char* pApplicationName, u32 applicationVersion, const char* pEngineName, u32 engineVersion,
	                                                  u32 apiVersion, const void* pNext = nullptr) noexcept {
		return VkApplicationInfo{
			.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
			.pNext = pNext,
			.pApplicationName = pApplicationName,
			.applicationVersion = applicationVersion,
			.pEngineName = pEngineName,
			.engineVersion = engineVersion,
			.apiVersion = apiVersion
		};
	}

	KML_FORCEINLINE VkInstanceCreateInfo InstanceCreateInfo(const VkApplicationInfo* pApplicationInfo, u32 enabledLayerCount,
	                                                        const char* const* ppEnabledLayerNames, u32 enabledExtensionCount,
	                                                        const char* const* ppEnabledExtensionNames,
	                                                        VkInstanceCreateFlags flags = 0, const void* pNext = nullptr) noexcept {
		return VkInstanceCreateInfo{
			.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.pApplicationInfo = pApplicationInfo,
			.enabledLayerCount = enabledLayerCount,
			.ppEnabledLayerNames = ppEnabledLayerNames,
			.enabledExtensionCount = enabledExtensionCount,
			.ppEnabledExtensionNames = ppEnabledExtensionNames
		};
	}

	KML_FORCEINLINE VkDebugUtilsMessengerCreateInfoEXT DebugUtilsMessengerCreateInfoEXT(VkDebugUtilsMessageSeverityFlagsEXT messageSeverity,
	                                                                                    VkDebugUtilsMessageTypeFlagsEXT messageType,
	                                                                                    PFN_vkDebugUtilsMessengerCallbackEXT pfnUserCallback,
	                                                                                    void* pUserData = nullptr,
	                                                                                    const void* pNext = nullptr,
	                                                                                    VkDebugUtilsMessengerCreateFlagsEXT flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
			.pNext = pNext,
			.flags = flags,
			.messageSeverity = messageSeverity,
			.messageType = messageType,
			.pfnUserCallback = pfnUserCallback,
			.pUserData = pUserData
		};
	}

	KML_FORCEINLINE VkDebugUtilsLabelEXT DebugUtilsLabelEXT(const char* pLabelName, f32 colorR, f32 colorG, f32 colorB, f32 colorA,
	                                                        const void* pNext = nullptr) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
			.pNext = pNext,
			.pLabelName = pLabelName,
			.color = {colorR, colorG, colorB, colorA}
		};
	}

	KML_FORCEINLINE VkDeviceQueueCreateInfo DeviceQueueCreateInfo(u32 queueFamilyIndex, u32 queueCount, const f32* pQueuePriorities,
	                                                              const void* pNext = nullptr, VkDeviceQueueCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.queueFamilyIndex = queueFamilyIndex,
			.queueCount = queueCount,
			.pQueuePriorities = pQueuePriorities
		};
	}

	KML_FORCEINLINE VkDeviceQueueInfo2 DeviceQueueInfo2(u32 queueFamilyIndex, u32 queueIndex, const void* pNext = nullptr,
	                                                    VkDeviceQueueCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2,
			.pNext = pNext,
			.flags = flags,
			.queueFamilyIndex = queueFamilyIndex,
			.queueIndex = queueIndex
		};
	}

	KML_FORCEINLINE VkDeviceCreateInfo DeviceCreateInfo(u32 queueCreateInfoCount, const VkDeviceQueueCreateInfo* pQueueCreateInfos,
	                                                    u32 enabledLayerCount, const char* const* ppEnabledLayerNames, u32 enabledExtensionCount,
	                                                    const char* const* ppEnabledExtensionNames,
	                                                    const VkPhysicalDeviceFeatures* pEnabledFeatures, const void* pNext = nullptr,
	                                                    VkDeviceCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.queueCreateInfoCount = queueCreateInfoCount,
			.pQueueCreateInfos = pQueueCreateInfos,
			.enabledLayerCount = enabledLayerCount,
			.ppEnabledLayerNames = ppEnabledLayerNames,
			.enabledExtensionCount = enabledExtensionCount,
			.ppEnabledExtensionNames = ppEnabledExtensionNames,
			.pEnabledFeatures = pEnabledFeatures,
		};
	}

	KML_FORCEINLINE VmaAllocatorCreateInfo AllocatorCreateInfo(VkPhysicalDevice physicalDevice, VkDevice device, VkInstance instance, u32 vulkanApiVersion,
	                                                           const VkAllocationCallbacks* pAllocationCallbacks, VkDeviceSize preferredLargeHeapBlockSize = 0,
	                                                           const VmaDeviceMemoryCallbacks* pDeviceMemoryCallbacks = nullptr,
	                                                           u32 frameInUseCount = 0, const VkDeviceSize* pHeapSizeLimit = nullptr,
	                                                           const VmaVulkanFunctions* pVulkanFunctions = nullptr,
	                                                           const VmaRecordSettings* pRecordSettings = nullptr, VmaAllocatorCreateFlags flags = 0) noexcept {
		return {
			.flags = flags,
			.physicalDevice = physicalDevice,
			.device = device,
			.preferredLargeHeapBlockSize = preferredLargeHeapBlockSize,
			.pAllocationCallbacks = pAllocationCallbacks,
			.pDeviceMemoryCallbacks = pDeviceMemoryCallbacks,
			.frameInUseCount = frameInUseCount,
			.pHeapSizeLimit = pHeapSizeLimit,
			.pVulkanFunctions = pVulkanFunctions,
			.pRecordSettings = pRecordSettings,
			.instance = instance,
			.vulkanApiVersion = vulkanApiVersion
		};
	}

	KML_FORCEINLINE VkPhysicalDeviceSurfaceInfo2KHR PhysicalDeviceSurfaceInfo2KHR(VkSurfaceKHR surface, const void* next = nullptr) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR,
			.pNext = next,
			.surface = surface
		};
	}
	
	KML_FORCEINLINE VkSwapchainCreateInfoKHR SwapchainCreateInfoKHR(VkSurfaceKHR surface, u32 minImageCount, VkFormat imageFormat, VkColorSpaceKHR imageColorSpace,
	                                                                const VkExtent2D& imageExtent, u32 imageArrayLayers, VkImageUsageFlags imageUsage,
	                                                                VkPresentModeKHR presentMode, VkSharingMode imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
	                                                                u32 queueFamilyIndexCount = 0, const u32* pQueueFamilyIndices = nullptr,
	                                                                VkSurfaceTransformFlagBitsKHR preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
	                                                                VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
	                                                                VkBool32 clipped = VK_TRUE, VkSwapchainKHR oldSwapchain = VK_NULL_HANDLE,
	                                                                const void* pNext = nullptr, VkSwapchainCreateFlagsKHR flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
			.pNext = pNext,
			.flags = flags,
			.surface = surface,
			.minImageCount = minImageCount,
			.imageFormat = imageFormat,
			.imageColorSpace = imageColorSpace,
			.imageExtent = imageExtent,
			.imageArrayLayers = imageArrayLayers,
			.imageUsage = imageUsage,
			.imageSharingMode = imageSharingMode,
			.queueFamilyIndexCount = queueFamilyIndexCount,
			.pQueueFamilyIndices = pQueueFamilyIndices,
			.preTransform = preTransform,
			.compositeAlpha = compositeAlpha,
			.presentMode = presentMode,
			.clipped = clipped,
			.oldSwapchain = oldSwapchain
		};
	}

	KML_FORCEINLINE VkFenceCreateInfo FenceCreateInfo(const void* pNext = nullptr, VkFenceCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags
		};
	}

	KML_FORCEINLINE VkSemaphoreCreateInfo SemaphoreCreateInfo(const void* pNext = nullptr, VkSemaphoreCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags
		};
	}

	KML_FORCEINLINE VkSubmitInfo SubmitInfo(u32 waitSemaphoreCount, const VkSemaphore* pWaitSemaphores, const VkPipelineStageFlags* pWaitDstStageMask,
	                                        u32 commandBufferCount, const VkCommandBuffer* pCommandBuffers, u32 signalSemaphoreCount,
	                                        const VkSemaphore* pSignalSemaphores, const void* pNext = nullptr) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
			.pNext = pNext,
			.waitSemaphoreCount = waitSemaphoreCount,
			.pWaitSemaphores = pWaitSemaphores,
			.pWaitDstStageMask = pWaitDstStageMask,
			.commandBufferCount = commandBufferCount,
			.pCommandBuffers = pCommandBuffers,
			.signalSemaphoreCount = signalSemaphoreCount,
			.pSignalSemaphores = pSignalSemaphores
		};
	}

	KML_FORCEINLINE VkPresentInfoKHR PresentInfo(u32 waitSemaphoreCount, const VkSemaphore* pWaitSemaphores, u32 swapchainCount, const VkSwapchainKHR* pSwapchains,
	                                             const u32* pImageIndices, VkResult* pResults, const void* pNext = nullptr) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
			.pNext = pNext,
			.waitSemaphoreCount = waitSemaphoreCount,
			.pWaitSemaphores = pWaitSemaphores,
			.swapchainCount = swapchainCount,
			.pSwapchains = pSwapchains,
			.pImageIndices = pImageIndices,
			.pResults = pResults
		};
	}

	KML_FORCEINLINE VkCommandPoolCreateInfo CommandPoolCreateInfo(u32 queueFamilyIndex, const void* pNext = nullptr, VkCommandPoolCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.queueFamilyIndex = queueFamilyIndex
		};
	}

	KML_FORCEINLINE VkCommandBufferAllocateInfo CommandBufferAllocateInfo(VkCommandPool commandPool, VkCommandBufferLevel level, u32 commandBufferCount,
	                                                                      const void* pNext = nullptr) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			.pNext = pNext,
			.commandPool = commandPool,
			.level = level,
			.commandBufferCount = commandBufferCount
		};
	}

	KML_FORCEINLINE VkCommandBufferBeginInfo CommandBufferBeginInfo(VkCommandBufferUsageFlags flags = 0,
	                                                                const VkCommandBufferInheritanceInfo* pInheritanceInfo = nullptr,
	                                                                const void* pNext = nullptr) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
			.pNext = pNext,
			.flags = flags,
			.pInheritanceInfo = pInheritanceInfo
		};
	}

	KML_FORCEINLINE VkDescriptorPoolSize DescriptorPoolSize(VkDescriptorType type, u32 descriptorCount) noexcept {
		return {
			.type = type,
			.descriptorCount = descriptorCount
		};
	}

	KML_FORCEINLINE VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo(u32 maxSets, u32 poolSizeCount, const VkDescriptorPoolSize* pPoolSizes,
	                                                                    const void* pNext = nullptr,
	                                                                    VkDescriptorPoolCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.maxSets = maxSets,
			.poolSizeCount = poolSizeCount,
			.pPoolSizes = pPoolSizes
		};
	}

	KML_FORCEINLINE VkDescriptorSetLayoutBindingFlagsCreateInfo DescriptorSetLayoutBindingFlagsCreateInfo(
		u32 bindingCount, const VkDescriptorBindingFlags* pBindingFlags,
		const void* pNext = nullptr) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
			.pNext = pNext,
			.bindingCount = bindingCount,
			.pBindingFlags = pBindingFlags
		};
	}

	KML_FORCEINLINE VkDescriptorSetVariableDescriptorCountAllocateInfo DescriptorSetVariableDescriptorCountAllocateInfo(
		u32 descriptorSetCount, const u32* pDescriptorCounts, const void* pNext = nullptr) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO,
			.pNext = pNext,
			.descriptorSetCount = descriptorSetCount,
			.pDescriptorCounts = pDescriptorCounts
		};
	}

	KML_FORCEINLINE VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo(u32 bindingCount, const VkDescriptorSetLayoutBinding* pBindings,
	                                                                              const void* pNext = nullptr, VkDescriptorSetLayoutCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.bindingCount = bindingCount,
			.pBindings = pBindings
		};
	}

	KML_FORCEINLINE VkDescriptorSetAllocateInfo DescriptorSetAllocateInfo(VkDescriptorPool descriptorPool, u32 descriptorSetCount,
	                                                                      const VkDescriptorSetLayout* pSetLayouts, const void* pNext = nullptr) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
			.pNext = pNext,
			.descriptorPool = descriptorPool,
			.descriptorSetCount = descriptorSetCount,
			.pSetLayouts = pSetLayouts
		};
	}

	KML_FORCEINLINE VkDescriptorBufferInfo DescriptorBufferInfo(VkBuffer buffer, VkDeviceSize range, VkDeviceSize offset = 0) noexcept {
		return {
			.buffer = buffer,
			.offset = offset,
			.range = range
		};
	}

	KML_FORCEINLINE VkDescriptorImageInfo DescriptorImageInfo(VkSampler sampler, VkImageView imageView, VkImageLayout imageLayout) noexcept {
		return {
			.sampler = sampler,
			.imageView = imageView,
			.imageLayout = imageLayout
		};
	}

	KML_FORCEINLINE VkWriteDescriptorSet WriteDescriptorSet(VkDescriptorSet dstSet, u32 dstBinding, u32 dstArrayElement, u32 descriptorCount,
	                                                        VkDescriptorType descriptorType, const VkDescriptorImageInfo* pImageInfo,
	                                                        const VkDescriptorBufferInfo* pBufferInfo = nullptr, const VkBufferView* pTexelBufferView = nullptr,
	                                                        const void* pNext = nullptr) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
			.pNext = pNext,
			.dstSet = dstSet,
			.dstBinding = dstBinding,
			.dstArrayElement = dstArrayElement,
			.descriptorCount = descriptorCount,
			.descriptorType = descriptorType,
			.pImageInfo = pImageInfo,
			.pBufferInfo = pBufferInfo,
			.pTexelBufferView = pTexelBufferView
		};
	}

	KML_FORCEINLINE VkDescriptorUpdateTemplateEntry DescriptorUpdateTemplateEntry(u32 dstBinding, u32 dstArrayElement, u32 descriptorCount,
	                                                                              VkDescriptorType descriptorType,
	                                                                              usize offset, usize stride) noexcept {
		return {
			.dstBinding = dstBinding,
			.dstArrayElement = dstArrayElement,
			.descriptorCount = descriptorCount,
			.descriptorType = descriptorType,
			.offset = offset,
			.stride = stride
		};
	}

	KML_FORCEINLINE VkDescriptorUpdateTemplateCreateInfo DescriptorUpdateTemplateCreateInfo(u32 descriptorUpdateEntryCount,
	                                                                                        const VkDescriptorUpdateTemplateEntry* pDescriptorUpdateEntries,
	                                                                                        VkDescriptorUpdateTemplateType templateType,
	                                                                                        VkDescriptorSetLayout descriptorSetLayout,
	                                                                                        VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout pipelineLayout,
	                                                                                        u32 set,
	                                                                                        const void* pNext = nullptr,
	                                                                                        VkDescriptorUpdateTemplateCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.descriptorUpdateEntryCount = descriptorUpdateEntryCount,
			.pDescriptorUpdateEntries = pDescriptorUpdateEntries,
			.templateType = templateType,
			.descriptorSetLayout = descriptorSetLayout,
			.pipelineBindPoint = pipelineBindPoint,
			.pipelineLayout = pipelineLayout,
			.set = set
		};
	}

	KML_FORCEINLINE VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo(u32 setLayoutCount, const VkDescriptorSetLayout* pSetLayouts,
	                                                                    u32 pushConstantRangeCount, const VkPushConstantRange* pPushConstantRanges,
	                                                                    const void* pNext = nullptr, VkPipelineLayoutCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.setLayoutCount = setLayoutCount,
			.pSetLayouts = pSetLayouts,
			.pushConstantRangeCount = pushConstantRangeCount,
			.pPushConstantRanges = pPushConstantRanges
		};
	}

	KML_FORCEINLINE VkBufferCreateInfo BufferCreateInfo(VkDeviceSize size, VkBufferUsageFlags usage, VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE,
	                                                    u32 queueFamilyIndexCount = 0, const u32* pQueueFamilyIndices = nullptr,
	                                                    const void* pNext = nullptr, VkBufferCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.size = size,
			.usage = usage,
			.sharingMode = sharingMode,
			.queueFamilyIndexCount = queueFamilyIndexCount,
			.pQueueFamilyIndices = pQueueFamilyIndices
		};
	}

	KML_FORCEINLINE VkImageCreateInfo ImageCreateInfo(VkImageType imageType, VkFormat format, VkExtent3D extent, u32 mipLevels, u32 arrayLayers,
	                                                  VkSampleCountFlagBits samples, VkImageUsageFlags usage,
	                                                  VkImageLayout initialLayout, VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL,
	                                                  VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE, u32 queueFamilyIndexCount = 0,
	                                                  const u32* pQueueFamilyIndices = nullptr,
	                                                  const void* pNext = nullptr, VkImageCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.imageType = imageType,
			.format = format,
			.extent = extent,
			.mipLevels = mipLevels,
			.arrayLayers = arrayLayers,
			.samples = samples,
			.tiling = tiling,
			.usage = usage,
			.sharingMode = sharingMode,
			.queueFamilyIndexCount = queueFamilyIndexCount,
			.pQueueFamilyIndices = pQueueFamilyIndices,
			.initialLayout = initialLayout
		};
	}

	KML_FORCEINLINE VkComponentMapping ComponentMapping(VkComponentSwizzle r = VK_COMPONENT_SWIZZLE_IDENTITY,
	                                                    VkComponentSwizzle g = VK_COMPONENT_SWIZZLE_IDENTITY, VkComponentSwizzle b = VK_COMPONENT_SWIZZLE_IDENTITY,
	                                                    VkComponentSwizzle a = VK_COMPONENT_SWIZZLE_IDENTITY) noexcept {
		return {
			.r = r,
			.g = g,
			.b = b,
			.a = a
		};
	}

	KML_FORCEINLINE VkImageViewCreateInfo ImageViewCreateInfo(VkImage image, VkImageViewType viewType, VkFormat format,
	                                                          const VkImageSubresourceRange subresourceRange,
	                                                          const VkComponentMapping& components = ComponentMapping(),
	                                                          const void* pNext = nullptr, VkImageViewCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.image = image,
			.viewType = viewType,
			.format = format,
			.components = components,
			.subresourceRange = subresourceRange
		};
	}

	KML_FORCEINLINE VmaAllocationCreateInfo AllocationCreateInfo(VmaMemoryUsage usage, VmaAllocationCreateFlags flags = 0, VkMemoryPropertyFlags requiredFlags = 0,
	                                                             VkMemoryPropertyFlags preferredFlags = 0, u32 memoryTypeBits = 0,
	                                                             VmaPool pool = VK_NULL_HANDLE, void* pUserData = nullptr) noexcept {
		return {
			.flags = flags,
			.usage = usage,
			.requiredFlags = requiredFlags,
			.preferredFlags = preferredFlags,
			.memoryTypeBits = memoryTypeBits,
			.pool = pool,
			.pUserData = pUserData
		};
	}

	KML_FORCEINLINE VkSamplerCreateInfo SamplerCreateInfo(VkFilter magFilter, VkFilter minFilter, VkSamplerMipmapMode mipmapMode, VkSamplerAddressMode addressModeU,
	                                                      VkSamplerAddressMode addressModeV, VkSamplerAddressMode addressModeW,
	                                                      f32 mipLodBias, VkBool32 anisotropyEnable, f32 maxAnisotropy, VkBool32 compareEnable = VK_FALSE,
	                                                      VkCompareOp compareOp = VK_COMPARE_OP_NEVER, f32 minLod = 0.0f, f32 maxLod = 1.0f,
	                                                      VkBorderColor borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK,
	                                                      VkBool32 unnormalizedCoordinates = VK_FALSE, const void* pNext = nullptr,
	                                                      VkSamplerCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.magFilter = magFilter,
			.minFilter = minFilter,
			.mipmapMode = mipmapMode,
			.addressModeU = addressModeU,
			.addressModeV = addressModeV,
			.addressModeW = addressModeW,
			.mipLodBias = mipLodBias,
			.anisotropyEnable = anisotropyEnable,
			.maxAnisotropy = maxAnisotropy,
			.compareEnable = compareEnable,
			.compareOp = compareOp,
			.minLod = minLod,
			.maxLod = maxLod,
			.borderColor = borderColor,
			.unnormalizedCoordinates = unnormalizedCoordinates
		};
	}

	KML_FORCEINLINE VkFramebufferCreateInfo FramebufferCreateInfo(VkRenderPass renderPass, u32 attachmentCount, const VkImageView* pAttachments, u32 width,
	                                                              u32 height, u32 layers,
	                                                              const void* pNext = nullptr, VkFramebufferCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.renderPass = renderPass,
			.attachmentCount = attachmentCount,
			.pAttachments = pAttachments,
			.width = width,
			.height = height,
			.layers = layers
		};
	}

	KML_FORCEINLINE VkSubpassDescription SubpassDescription(VkPipelineBindPoint pipelineBindPoint, u32 colorAttachmentCount,
	                                                        const VkAttachmentReference* pColorAttachments, const VkAttachmentReference* pDepthStencilAttachment,
	                                                        u32 inputAttachmentCount = 0, const VkAttachmentReference* pInputAttachments = nullptr,
	                                                        const VkAttachmentReference* pResolveAttachments = nullptr, u32 preserveAttachmentCount = 0,
	                                                        const u32* pPreserveAttachments = nullptr,
	                                                        VkSubpassDescriptionFlags flags = 0) noexcept {
		return {
			.flags = flags,
			.pipelineBindPoint = pipelineBindPoint,
			.inputAttachmentCount = inputAttachmentCount,
			.pInputAttachments = pInputAttachments,
			.colorAttachmentCount = colorAttachmentCount,
			.pColorAttachments = pColorAttachments,
			.pResolveAttachments = pResolveAttachments,
			.pDepthStencilAttachment = pDepthStencilAttachment,
			.preserveAttachmentCount = preserveAttachmentCount,
			.pPreserveAttachments = pPreserveAttachments
		};
	}

	KML_FORCEINLINE VkAttachmentDescription AttachmentDescription(VkFormat format, VkSampleCountFlagBits samples, VkAttachmentLoadOp loadOp,
	                                                              VkAttachmentStoreOp storeOp, VkImageLayout initialLayout, VkImageLayout finalLayout,
	                                                              VkAttachmentLoadOp stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
	                                                              VkAttachmentStoreOp stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
	                                                              VkAttachmentDescriptionFlags flags = 0) noexcept {
		return {
			.flags = flags,
			.format = format,
			.samples = samples,
			.loadOp = loadOp,
			.storeOp = storeOp,
			.stencilLoadOp = stencilLoadOp,
			.stencilStoreOp = stencilStoreOp,
			.initialLayout = initialLayout,
			.finalLayout = finalLayout
		};
	}

	KML_FORCEINLINE VkAttachmentReference AttachmentReference(u32 attachment, VkImageLayout layout) noexcept {
		return
		{
			.attachment = attachment,
			.layout = layout
		};
	}

	KML_FORCEINLINE VkRenderPassCreateInfo RenderPassCreateInfo(u32 attachmentCount, const VkAttachmentDescription* pAttachments,
	                                                            uint32_t subpassCount, const VkSubpassDescription* pSubpasses, u32 dependencyCount = 0,
	                                                            const VkSubpassDependency* pDependencies = nullptr,
	                                                            const void* pNext = nullptr, VkRenderPassCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.attachmentCount = attachmentCount,
			.pAttachments = pAttachments,
			.subpassCount = subpassCount,
			.pSubpasses = pSubpasses,
			.dependencyCount = dependencyCount,
			.pDependencies = pDependencies
		};
	}

	KML_FORCEINLINE VkRenderPassBeginInfo RenderPassBeginInfo(VkRenderPass renderPass, VkFramebuffer framebuffer, const VkOffset2D& offset, const VkExtent2D& extent,
	                                                          u32 clearValueCount, const VkClearValue* pClearValues, const void* pNext = nullptr) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
			.pNext = pNext,
			.renderPass = renderPass,
			.framebuffer = framebuffer,
			.renderArea = {.offset = offset, .extent = extent},
			.clearValueCount = clearValueCount,
			.pClearValues = pClearValues
		};
	}

	KML_FORCEINLINE VkSubpassDependency SubpassDependency(u32 srcSubpass, u32 dstSubpass, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask,
	                                                      VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask, VkDependencyFlags dependencyFlags) noexcept {
		return {
			.srcSubpass = srcSubpass,
			.dstSubpass = dstSubpass,
			.srcStageMask = srcStageMask,
			.dstStageMask = dstStageMask,
			.srcAccessMask = srcAccessMask,
			.dstAccessMask = dstAccessMask,
			.dependencyFlags = dependencyFlags
		};
	}

	KML_FORCEINLINE VkShaderModuleCreateInfo ShaderModuleCreateInfo(usize codeSize, const u32* pCode, const void* pNext = nullptr,
	                                                                VkShaderModuleCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.codeSize = codeSize,
			.pCode = pCode
		};
	}

	KML_FORCEINLINE VkVertexInputBindingDescription VertexInputBindingDescription(u32 binding, u32 stride, VkVertexInputRate inputRate) noexcept {
		return {
			.binding = binding,
			.stride = stride,
			.inputRate = inputRate
		};
	}

	KML_FORCEINLINE VkVertexInputAttributeDescription VertexInputAttributeDescription(u32 location, u32 binding, VkFormat format, u32 offset) noexcept {
		return {
			.location = location,
			.binding = binding,
			.format = format,
			.offset = offset
		};
	}

	KML_FORCEINLINE VkPipelineShaderStageCreateInfo PipelineShaderStageCreateInfo(VkShaderStageFlagBits stage, VkShaderModule module, const char* pName,
	                                                                              const VkSpecializationInfo* pSpecializationInfo, const void* pNext = nullptr,
	                                                                              VkPipelineShaderStageCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.stage = stage,
			.module = module,
			.pName = pName,
			.pSpecializationInfo = pSpecializationInfo
		};
	}

	KML_FORCEINLINE VkPipelineInputAssemblyStateCreateInfo PipelineInputAssemblyStateCreateInfo(VkPrimitiveTopology topology,
	                                                                                            VkBool32 primitiveRestartEnable = VK_FALSE,
	                                                                                            const void* pNext = nullptr,
	                                                                                            VkPipelineInputAssemblyStateCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = flags,
			.topology = topology,
			.primitiveRestartEnable = primitiveRestartEnable
		};
	}

	KML_FORCEINLINE VkPipelineTessellationStateCreateInfo PipelineTessellationStateCreateInfo(u32 patchControlPoints,
	                                                                                          const void* pNext = nullptr,
	                                                                                          VkPipelineTessellationStateCreateFlags flags = 0) {
		return {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.patchControlPoints = patchControlPoints
		};
	}

	KML_FORCEINLINE VkPipelineRasterizationStateCreateInfo PipelineRasterizationStateCreateInfo(VkPolygonMode polygonMode, VkCullModeFlags cullMode,
	                                                                                            VkFrontFace frontFace, VkBool32 depthClampEnable = VK_FALSE,
	                                                                                            VkBool32 rasterizerDiscardEnable = VK_FALSE,
	                                                                                            VkBool32 depthBiasEnable = VK_FALSE,
	                                                                                            f32 depthBiasConstantFactor = 0.0f, f32 depthBiasClamp = 0.0f,
	                                                                                            f32 depthBiasSlopeFactor = 0.0f, f32 lineWidth = 1.0f,
	                                                                                            VkPipelineRasterizationStateCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
			.pNext = nullptr,
			.flags = flags,
			.depthClampEnable = depthClampEnable,
			.rasterizerDiscardEnable = rasterizerDiscardEnable,
			.polygonMode = polygonMode,
			.cullMode = cullMode,
			.frontFace = frontFace,
			.depthBiasEnable = depthBiasEnable,
			.depthBiasConstantFactor = depthBiasConstantFactor,
			.depthBiasClamp = depthBiasClamp,
			.depthBiasSlopeFactor = depthBiasSlopeFactor,
			.lineWidth = lineWidth
		};
	}

	KML_FORCEINLINE VkPipelineMultisampleStateCreateInfo PipelineMultisampleStateCreateInfo(VkSampleCountFlagBits rasterizationSamples,
	                                                                                        VkBool32 sampleShadingEnable = VK_FALSE, f32 minSampleShading = 0.0f,
	                                                                                        const VkSampleMask* pSampleMask = nullptr,
	                                                                                        VkBool32 alphaToCoverageEnable = VK_FALSE,
	                                                                                        VkBool32 alphaToOneEnable = VK_FALSE,
	                                                                                        const void* pNext = nullptr,
	                                                                                        VkPipelineMultisampleStateCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.rasterizationSamples = rasterizationSamples,
			.sampleShadingEnable = sampleShadingEnable,
			.minSampleShading = minSampleShading,
			.pSampleMask = pSampleMask,
			.alphaToCoverageEnable = alphaToCoverageEnable,
			.alphaToOneEnable = alphaToOneEnable
		};
	}

	KML_FORCEINLINE VkPipelineDepthStencilStateCreateInfo PipelineDepthStencilStateCreateInfo(VkBool32 depthTestEnable, VkBool32 depthWriteEnable,
	                                                                                          VkCompareOp depthCompareOp, VkBool32 depthBoundsTestEnable = VK_FALSE,
	                                                                                          VkBool32 stencilTestEnable = VK_FALSE,
	                                                                                          const VkStencilOpState& front = {}, const VkStencilOpState& back = {},
	                                                                                          f32 minDepthBounds = 0.0f, f32 maxDepthBounds = 1.0f,
	                                                                                          const void* pNext = nullptr,
	                                                                                          VkPipelineDepthStencilStateCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.depthTestEnable = depthTestEnable,
			.depthWriteEnable = depthWriteEnable,
			.depthCompareOp = depthCompareOp,
			.depthBoundsTestEnable = depthBoundsTestEnable,
			.stencilTestEnable = stencilTestEnable,
			.front = front,
			.back = back,
			.minDepthBounds = minDepthBounds,
			.maxDepthBounds = maxDepthBounds
		};
	}

	KML_FORCEINLINE VkPipelineColorBlendAttachmentState PipelineColorBlendAttachmentState(VkBool32 blendEnable = VK_FALSE,
	                                                                                      VkBlendFactor srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
	                                                                                      VkBlendFactor dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
	                                                                                      VkBlendOp colorBlendOp = VK_BLEND_OP_ADD,
	                                                                                      VkBlendFactor srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
	                                                                                      VkBlendFactor dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
	                                                                                      VkBlendOp alphaBlendOp = VK_BLEND_OP_ADD,
	                                                                                      VkColorComponentFlags colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
	                                                                                      VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
	                                                                                      VK_COLOR_COMPONENT_A_BIT) noexcept {
		return {
			.blendEnable = blendEnable,
			.srcColorBlendFactor = srcColorBlendFactor,
			.dstColorBlendFactor = dstColorBlendFactor,
			.colorBlendOp = colorBlendOp,
			.srcAlphaBlendFactor = srcAlphaBlendFactor,
			.dstAlphaBlendFactor = dstAlphaBlendFactor,
			.alphaBlendOp = alphaBlendOp,
			.colorWriteMask = colorWriteMask
		};
	}

	KML_FORCEINLINE VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateCreateInfo(u32 vertexBindingDescriptionCount,
	                                                                                        const VkVertexInputBindingDescription* pVertexBindingDescriptions,
	                                                                                        u32 vertexAttributeDescriptionCount,
	                                                                                        const VkVertexInputAttributeDescription* pVertexAttributeDescriptions,
	                                                                                        const void* pNext = nullptr,
	                                                                                        VkPipelineVertexInputStateCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.vertexBindingDescriptionCount = vertexBindingDescriptionCount,
			.pVertexBindingDescriptions = pVertexBindingDescriptions,
			.vertexAttributeDescriptionCount = vertexAttributeDescriptionCount,
			.pVertexAttributeDescriptions = pVertexAttributeDescriptions
		};
	}

	KML_FORCEINLINE VkPipelineViewportStateCreateInfo PipelineViewportStateCreateInfo(u32 viewportCount, const VkViewport* pViewports,
	                                                                                  u32 scissorCount, const VkRect2D* pScissors, const void* pNext = nullptr,
	                                                                                  VkPipelineViewportStateCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.viewportCount = viewportCount,
			.pViewports = pViewports,
			.scissorCount = scissorCount,
			.pScissors = pScissors
		};
	}

	KML_FORCEINLINE VkPipelineColorBlendStateCreateInfo PipelineColorBlendStateCreateInfo(VkBool32 logicOpEnable, VkLogicOp logicOp,
	                                                                                      u32 attachmentCount,
	                                                                                      const VkPipelineColorBlendAttachmentState* pAttachments,
	                                                                                      f32 blendConstantsR = 1.0f, f32 blendConstantsG = 0.0f,
	                                                                                      f32 blendConstantsB = 1.0f,
	                                                                                      f32 blendConstantsA = 0.0f, const void* pNext = nullptr,
	                                                                                      VkPipelineColorBlendStateCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
			.pNext = pNext,
			.flags = 0,
			.logicOpEnable = logicOpEnable,
			.logicOp = logicOp,
			.attachmentCount = attachmentCount,
			.pAttachments = pAttachments,
			.blendConstants = {blendConstantsR, blendConstantsG, blendConstantsB, blendConstantsA}
		};
	}

	KML_FORCEINLINE VkPipelineDynamicStateCreateInfo PipelineDynamicStateCreateInfo(u32 dynamicStateCount, const VkDynamicState* pDynamicStates,
	                                                                                const void* pNext = nullptr,
	                                                                                VkPipelineDynamicStateCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.dynamicStateCount = dynamicStateCount,
			.pDynamicStates = pDynamicStates
		};
	}

	KML_FORCEINLINE VkGraphicsPipelineCreateInfo GraphicsPipelineCreateInfo(u32 stageCount, const VkPipelineShaderStageCreateInfo* pStages,
	                                                                        const VkPipelineVertexInputStateCreateInfo* pVertexInputState,
	                                                                        const VkPipelineInputAssemblyStateCreateInfo* pInputAssemblyState,
	                                                                        const VkPipelineTessellationStateCreateInfo* pTessellationState,
	                                                                        const VkPipelineViewportStateCreateInfo* pViewportState,
	                                                                        const VkPipelineRasterizationStateCreateInfo* pRasterizationState,
	                                                                        const VkPipelineMultisampleStateCreateInfo* pMultisampleState,
	                                                                        const VkPipelineDepthStencilStateCreateInfo* pDepthStencilState,
	                                                                        const VkPipelineColorBlendStateCreateInfo* pColorBlendState,
	                                                                        const VkPipelineDynamicStateCreateInfo* pDynamicState, VkPipelineLayout layout,
	                                                                        VkRenderPass renderPass, u32 subpass,
	                                                                        VkPipeline basePipelineHandle = VK_NULL_HANDLE, i32 basePipelineIndex = -1,
	                                                                        const void* pNext = nullptr, VkPipelineCreateFlags flags = 0) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
			.pNext = pNext,
			.flags = flags,
			.stageCount = stageCount,
			.pStages = pStages,
			.pVertexInputState = pVertexInputState,
			.pInputAssemblyState = pInputAssemblyState,
			.pTessellationState = pTessellationState,
			.pViewportState = pViewportState,
			.pRasterizationState = pRasterizationState,
			.pMultisampleState = pMultisampleState,
			.pDepthStencilState = pDepthStencilState,
			.pColorBlendState = pColorBlendState,
			.pDynamicState = pDynamicState,
			.layout = layout,
			.renderPass = renderPass,
			.subpass = subpass,
			.basePipelineHandle = basePipelineHandle,
			.basePipelineIndex = basePipelineIndex
		};
	}

	KML_FORCEINLINE VkComputePipelineCreateInfo ComputePipelineCreateInfo(const VkPipelineShaderStageCreateInfo& stage,
                                                                          VkPipelineLayout layout,
                                                                          VkPipeline basePipelineHandle = VK_NULL_HANDLE,
                                                                          i32 basePipelineIndex = -1,
                                                                          const void* pNext = nullptr,
                                                                          VkPipelineCreateFlags flags = 0) noexcept {
	    return {
	        .sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
	        .pNext = pNext,
	        .flags = flags,
	        .stage = stage,
	        .layout = layout,
	        .basePipelineHandle = basePipelineHandle,
	        .basePipelineIndex = basePipelineIndex
	    };
	}

	KML_FORCEINLINE VkBufferCopy BufferCopy(VkDeviceSize size, VkDeviceSize srcOffset = 0, VkDeviceSize dstOffset = 0) noexcept {
		return {
			.srcOffset = srcOffset,
			.dstOffset = dstOffset,
			.size = size
		};
	}

	KML_FORCEINLINE VkBufferImageCopy BufferImageCopy(VkDeviceSize bufferOffset, u32 bufferRowLength, u32 bufferImageHeight,
	                                                  const VkImageSubresourceLayers& imageSubresource, const VkOffset3D& imageOffset,
	                                                  const VkExtent3D& imageExtent) noexcept {
		return {
			.bufferOffset = bufferOffset,
			.bufferRowLength = bufferRowLength,
			.bufferImageHeight = bufferImageHeight,
			.imageSubresource = imageSubresource,
			.imageOffset = imageOffset,
			.imageExtent = imageExtent,
		};
	}

	KML_FORCEINLINE VkImageBlit ImageBlit(const VkImageSubresourceLayers& srcSubresource, const VkOffset3D srcOffsets[2],
	                                      const VkImageSubresourceLayers& dstSubresource, const VkOffset3D dstOffsets[2]) noexcept {
		VkImageBlit imageBlit;
		imageBlit.srcSubresource = srcSubresource;
		imageBlit.srcOffsets[0] = srcOffsets[0];
		imageBlit.srcOffsets[1] = srcOffsets[1];
		imageBlit.dstSubresource = dstSubresource;
		imageBlit.dstOffsets[0] = dstOffsets[0];
		imageBlit.dstOffsets[1] = dstOffsets[1];

		return imageBlit;
	}

	KML_FORCEINLINE VkMemoryBarrier MemoryBarrier(VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask, const void* pNext = nullptr) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER,
			.pNext = pNext,
			.srcAccessMask = srcAccessMask,
			.dstAccessMask = dstAccessMask
		};
	}

	KML_FORCEINLINE VkImageMemoryBarrier ImageMemoryBarrier(VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask, VkImageLayout oldLayout,
	                                                        VkImageLayout newLayout, u32 srcQueueFamilyIndex, u32 dstQueueFamilyIndex, VkImage image,
	                                                        const VkImageSubresourceRange& subresourceRange,
	                                                        const void* pNext = nullptr) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
			.pNext = pNext,
			.srcAccessMask = srcAccessMask,
			.dstAccessMask = dstAccessMask,
			.oldLayout = oldLayout,
			.newLayout = newLayout,
			.srcQueueFamilyIndex = srcQueueFamilyIndex,
			.dstQueueFamilyIndex = dstQueueFamilyIndex,
			.image = image,
			.subresourceRange = subresourceRange
		};
	}

	KML_FORCEINLINE VkQueryPoolCreateInfo QueryPoolCreateInfo(VkQueryType queryType, u32 queryCount, VkQueryPipelineStatisticFlags pipelineStatistics, VkQueryPoolCreateFlags flags = 0, const void* next = nullptr) noexcept {
		return {
			.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO,
			.pNext = next,
			.flags = flags,
			.queryType = queryType,
			.queryCount = queryCount,
			.pipelineStatistics = pipelineStatistics,
		};
	}

	//Conversion functions
	KML_FORCEINLINE VkClearValue ClearValueFromColor(const Color4f& color) noexcept {
		VkClearValue clearValue;
		clearValue.color.float32[0] = color.R;
		clearValue.color.float32[1] = color.G;
		clearValue.color.float32[2] = color.B;
		clearValue.color.float32[3] = color.A;

		return clearValue;
	}

	KML_FORCEINLINE VkClearValue DepthStencilClearValue(f32 depth, u8 stencil) noexcept {
		VkClearValue clearValue;
		clearValue.depthStencil.depth = depth;
		clearValue.depthStencil.stencil = stencil;

		return clearValue;
	}

	KML_FORCEINLINE VkViewport ViewportFromSize(const PointU32& size) noexcept {
		return Viewport(0.0f, 0.0f, static_cast<f32>(size.X), static_cast<f32>(size.Y));
	}

	KML_FORCEINLINE VkRect2D Rect2DFromSize(const PointU32& size) noexcept {
		return Rect2D(0, 0, size.X, size.Y);
	}
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_VULKANUTILS_HPP
﻿//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanTypes.cpp
//------------------------------------------------------------

#include "VulkanTypes.hpp"

namespace KMLEngine::Vulkan::Types {
	using namespace std::string_view_literals;
	
	namespace Result {	
		std::string_view ToString(VkResult result) noexcept {
			switch(result) {
				case VK_SUCCESS: return "VK_SUCCESS"sv;
				case VK_NOT_READY: return "VK_NOT_READY"sv;
				case VK_TIMEOUT: return "VK_TIMEOUT"sv;
				case VK_EVENT_SET: return "VK_EVENT_SET"sv;
				case VK_EVENT_RESET: return "VK_EVENT_RESET"sv;
				case VK_INCOMPLETE: return "VK_INCOMPLETE"sv;
				case VK_ERROR_OUT_OF_HOST_MEMORY: return "VK_ERROR_OUT_OF_HOST_MEMORY"sv;
				case VK_ERROR_OUT_OF_DEVICE_MEMORY: return "VK_ERROR_OUT_OF_DEVICE_MEMORY"sv;
				case VK_ERROR_INITIALIZATION_FAILED: return "VK_ERROR_INITIALIZATION_FAILED"sv;
				case VK_ERROR_DEVICE_LOST: return "VK_ERROR_DEVICE_LOST"sv;
				case VK_ERROR_MEMORY_MAP_FAILED: return "VK_ERROR_MEMORY_MAP_FAILED"sv;
				case VK_ERROR_LAYER_NOT_PRESENT: return "VK_ERROR_LAYER_NOT_PRESENT"sv;
				case VK_ERROR_EXTENSION_NOT_PRESENT: return "VK_ERROR_EXTENSION_NOT_PRESENT"sv;
				case VK_ERROR_FEATURE_NOT_PRESENT: return "VK_ERROR_FEATURE_NOT_PRESENT"sv;
				case VK_ERROR_INCOMPATIBLE_DRIVER: return "VK_ERROR_INCOMPATIBLE_DRIVER"sv;
				case VK_ERROR_TOO_MANY_OBJECTS: return "VK_ERROR_TOO_MANY_OBJECTS"sv;
				case VK_ERROR_FORMAT_NOT_SUPPORTED: return "VK_ERROR_FORMAT_NOT_SUPPORTED"sv;
				case VK_ERROR_FRAGMENTED_POOL: return "VK_ERROR_FRAGMENTED_POOL"sv;
				case VK_ERROR_UNKNOWN: return "VK_ERROR_UNKNOWN"sv;
				case VK_ERROR_OUT_OF_POOL_MEMORY: return "VK_ERROR_OUT_OF_POOL_MEMORY"sv;
				case VK_ERROR_INVALID_EXTERNAL_HANDLE: return "VK_ERROR_INVALID_EXTERNAL_HANDLE"sv;
				case VK_ERROR_FRAGMENTATION: return "VK_ERROR_FRAGMENTATION"sv;
				case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS"sv;
				case VK_ERROR_SURFACE_LOST_KHR: return "VK_ERROR_SURFACE_LOST_KHR"sv;
				case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR"sv;
				case VK_SUBOPTIMAL_KHR: return "VK_SUBOPTIMAL_KHR"sv;
				case VK_ERROR_OUT_OF_DATE_KHR: return "VK_ERROR_OUT_OF_DATE_KHR"sv;
				case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR"sv;
				case VK_ERROR_VALIDATION_FAILED_EXT: return "VK_ERROR_VALIDATION_FAILED_EXT"sv;
				case VK_ERROR_INVALID_SHADER_NV: return "VK_ERROR_INVALID_SHADER_NV"sv;
				case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: return "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT"sv;
				case VK_ERROR_NOT_PERMITTED_EXT: return "VK_ERROR_NOT_PERMITTED_EXT"sv;
				case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT"sv;
				case VK_THREAD_IDLE_KHR: return "VK_THREAD_IDLE_KHR"sv;
				case VK_THREAD_DONE_KHR: return "VK_THREAD_DONE_KHR"sv;
				case VK_OPERATION_DEFERRED_KHR: return "VK_OPERATION_DEFERRED_KHR"sv;
				case VK_OPERATION_NOT_DEFERRED_KHR: return "VK_OPERATION_NOT_DEFERRED_KHR"sv;
				case VK_PIPELINE_COMPILE_REQUIRED_EXT: return "VK_PIPELINE_COMPILE_REQUIRED_EXT"sv;
				default:
					spdlog::warn("Unknown {}: {}", "VkResult", static_cast<u32>(result));
					return "UNKNOWN"sv;
			}
		}
	}

	namespace ObjectType {
		std::string_view ToString(VkObjectType objectType) noexcept {
			switch(objectType) {
				case VK_OBJECT_TYPE_UNKNOWN: return "VK_OBJECT_TYPE_UNKNOWN"sv;
				case VK_OBJECT_TYPE_INSTANCE: return "VK_OBJECT_TYPE_INSTANCE"sv;
				case VK_OBJECT_TYPE_PHYSICAL_DEVICE: return "VK_OBJECT_TYPE_PHYSICAL_DEVICE"sv;
				case VK_OBJECT_TYPE_DEVICE: return "VK_OBJECT_TYPE_DEVICE"sv;
				case VK_OBJECT_TYPE_QUEUE: return "VK_OBJECT_TYPE_QUEUE"sv;
				case VK_OBJECT_TYPE_SEMAPHORE: return "VK_OBJECT_TYPE_SEMAPHORE"sv;
				case VK_OBJECT_TYPE_COMMAND_BUFFER: return "VK_OBJECT_TYPE_COMMAND_BUFFER"sv;
				case VK_OBJECT_TYPE_FENCE: return "VK_OBJECT_TYPE_FENCE"sv;
				case VK_OBJECT_TYPE_DEVICE_MEMORY: return "VK_OBJECT_TYPE_DEVICE_MEMORY"sv;
				case VK_OBJECT_TYPE_BUFFER: return "VK_OBJECT_TYPE_BUFFER"sv;
				case VK_OBJECT_TYPE_IMAGE: return "VK_OBJECT_TYPE_IMAGE"sv;
				case VK_OBJECT_TYPE_EVENT: return "VK_OBJECT_TYPE_EVENT"sv;
				case VK_OBJECT_TYPE_QUERY_POOL: return "VK_OBJECT_TYPE_QUERY_POOL"sv;
				case VK_OBJECT_TYPE_BUFFER_VIEW: return "VK_OBJECT_TYPE_BUFFER_VIEW"sv;
				case VK_OBJECT_TYPE_IMAGE_VIEW: return "VK_OBJECT_TYPE_IMAGE_VIEW"sv;
				case VK_OBJECT_TYPE_SHADER_MODULE: return "VK_OBJECT_TYPE_SHADER_MODULE"sv;
				case VK_OBJECT_TYPE_PIPELINE_CACHE: return "VK_OBJECT_TYPE_PIPELINE_CACHE"sv;
				case VK_OBJECT_TYPE_PIPELINE_LAYOUT: return "VK_OBJECT_TYPE_PIPELINE_LAYOUT"sv;
				case VK_OBJECT_TYPE_RENDER_PASS: return "VK_OBJECT_TYPE_RENDER_PASS"sv;
				case VK_OBJECT_TYPE_PIPELINE: return "VK_OBJECT_TYPE_PIPELINE"sv;
				case VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT: return "VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT"sv;
				case VK_OBJECT_TYPE_SAMPLER: return "VK_OBJECT_TYPE_SAMPLER"sv;
				case VK_OBJECT_TYPE_DESCRIPTOR_POOL: return "VK_OBJECT_TYPE_DESCRIPTOR_POOL"sv;
				case VK_OBJECT_TYPE_DESCRIPTOR_SET: return "VK_OBJECT_TYPE_DESCRIPTOR_SET"sv;
				case VK_OBJECT_TYPE_FRAMEBUFFER: return "VK_OBJECT_TYPE_FRAMEBUFFER"sv;
				case VK_OBJECT_TYPE_COMMAND_POOL: return "VK_OBJECT_TYPE_COMMAND_POOL"sv;
				case VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION: return "VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION"sv;
				case VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE: return "VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE"sv;
				case VK_OBJECT_TYPE_SURFACE_KHR: return "VK_OBJECT_TYPE_SURFACE_KHR"sv;
				case VK_OBJECT_TYPE_SWAPCHAIN_KHR: return "VK_OBJECT_TYPE_SWAPCHAIN_KHR"sv;
				case VK_OBJECT_TYPE_DISPLAY_KHR: return "VK_OBJECT_TYPE_DISPLAY_KHR"sv;
				case VK_OBJECT_TYPE_DISPLAY_MODE_KHR: return "VK_OBJECT_TYPE_DISPLAY_MODE_KHR"sv;
				case VK_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT: return "VK_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT"sv;
				case VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT: return "VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT"sv;
				case VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR: return "VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR"sv;
				case VK_OBJECT_TYPE_VALIDATION_CACHE_EXT: return "VK_OBJECT_TYPE_VALIDATION_CACHE_EXT"sv;
				case VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV: return "VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV"sv;
				case VK_OBJECT_TYPE_PERFORMANCE_CONFIGURATION_INTEL: return "VK_OBJECT_TYPE_PERFORMANCE_CONFIGURATION_INTEL"sv;
				case VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR: return "VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR"sv;
				case VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NV: return "VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NV"sv;
				case VK_OBJECT_TYPE_PRIVATE_DATA_SLOT_EXT: return "VK_OBJECT_TYPE_PRIVATE_DATA_SLOT_EXT"sv;
				default:
					spdlog::warn("Invalid {}: {}", "VkObjectType", static_cast<u32>(objectType));
					return "UNKNOWN"sv;
			}
		}
	}

	namespace MessageSeverity {
		spdlog::level::level_enum ToLogLevel(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity) noexcept {
			switch(messageSeverity) {
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
					return spdlog::level::level_enum::info;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
					return spdlog::level::level_enum::warn;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
					return spdlog::level::level_enum::err;
				default:
					spdlog::warn("Invalid {}: {}", "VkDebugUtilsMessageSeverityFlagBitsEXT", static_cast<u32>(messageSeverity));
					return spdlog::level::level_enum::info;
			}
		}
		
		std::string_view ToString(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity) noexcept {
			switch(messageSeverity) {
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT"sv;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT"sv;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT"sv;
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: return "VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT"sv;
				default:
					spdlog::warn("Invalid {}: {}", "VkDebugUtilsMessageSeverityFlagBitsEXT", static_cast<u32>(messageSeverity));
					return "UNKNOWN"sv;
			}
		}
	}

	namespace PresentMode {
		std::string_view ToString(VkPresentModeKHR presentMode) noexcept {
			switch(presentMode) {
				case VK_PRESENT_MODE_IMMEDIATE_KHR: return "VK_PRESENT_MODE_IMMEDIATE_KHR"sv;
				case VK_PRESENT_MODE_MAILBOX_KHR: return "VK_PRESENT_MODE_MAILBOX_KHR"sv;
				case VK_PRESENT_MODE_FIFO_KHR: return "VK_PRESENT_MODE_FIFO_KHR"sv;
				case VK_PRESENT_MODE_FIFO_RELAXED_KHR: return "VK_PRESENT_MODE_FIFO_RELAXED_KHR"sv;
				case VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR: return "VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR"sv;
				case VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR: return "VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR"sv;
				default:
					spdlog::warn("Invalid {}: {}", "VkPresentModeKHR", static_cast<u32>(presentMode));
					return "UNKNOWN"sv;
			}
		}
	}

	namespace Format {
		std::string_view ToString(VkFormat format) noexcept {
			switch(format) {
				case VK_FORMAT_UNDEFINED: return "VK_FORMAT_UNDEFINED"sv;
				case VK_FORMAT_R4G4_UNORM_PACK8: return "VK_FORMAT_R4G4_UNORM_PACK8"sv;
				case VK_FORMAT_R4G4B4A4_UNORM_PACK16: return "VK_FORMAT_R4G4B4A4_UNORM_PACK16"sv;
				case VK_FORMAT_B4G4R4A4_UNORM_PACK16: return "VK_FORMAT_B4G4R4A4_UNORM_PACK16"sv;
				case VK_FORMAT_R5G6B5_UNORM_PACK16: return "VK_FORMAT_R5G6B5_UNORM_PACK16"sv;
				case VK_FORMAT_B5G6R5_UNORM_PACK16: return "VK_FORMAT_B5G6R5_UNORM_PACK16"sv;
				case VK_FORMAT_R5G5B5A1_UNORM_PACK16: return "VK_FORMAT_R5G5B5A1_UNORM_PACK16"sv;
				case VK_FORMAT_B5G5R5A1_UNORM_PACK16: return "VK_FORMAT_B5G5R5A1_UNORM_PACK16"sv;
				case VK_FORMAT_A1R5G5B5_UNORM_PACK16: return "VK_FORMAT_A1R5G5B5_UNORM_PACK16"sv;
				case VK_FORMAT_R8_UNORM: return "VK_FORMAT_R8_UNORM"sv;
				case VK_FORMAT_R8_SNORM: return "VK_FORMAT_R8_SNORM"sv;
				case VK_FORMAT_R8_USCALED: return "VK_FORMAT_R8_USCALED"sv;
				case VK_FORMAT_R8_SSCALED: return "VK_FORMAT_R8_SSCALED"sv;
				case VK_FORMAT_R8_UINT: return "VK_FORMAT_R8_UINT"sv;
				case VK_FORMAT_R8_SINT: return "VK_FORMAT_R8_SINT"sv;
				case VK_FORMAT_R8_SRGB: return "VK_FORMAT_R8_SRGB"sv;
				case VK_FORMAT_R8G8_UNORM: return "VK_FORMAT_R8G8_UNORM"sv;
				case VK_FORMAT_R8G8_SNORM: return "VK_FORMAT_R8G8_SNORM"sv;
				case VK_FORMAT_R8G8_USCALED: return "VK_FORMAT_R8G8_USCALED"sv;
				case VK_FORMAT_R8G8_SSCALED: return "VK_FORMAT_R8G8_SSCALED"sv;
				case VK_FORMAT_R8G8_UINT: return "VK_FORMAT_R8G8_UINT"sv;
				case VK_FORMAT_R8G8_SINT: return "VK_FORMAT_R8G8_SINT"sv;
				case VK_FORMAT_R8G8_SRGB: return "VK_FORMAT_R8G8_SRGB"sv;
				case VK_FORMAT_R8G8B8_UNORM: return "VK_FORMAT_R8G8B8_UNORM"sv;
				case VK_FORMAT_R8G8B8_SNORM: return "VK_FORMAT_R8G8B8_SNORM"sv;
				case VK_FORMAT_R8G8B8_USCALED: return "VK_FORMAT_R8G8B8_USCALED"sv;
				case VK_FORMAT_R8G8B8_SSCALED: return "VK_FORMAT_R8G8B8_SSCALED"sv;
				case VK_FORMAT_R8G8B8_UINT: return "VK_FORMAT_R8G8B8_UINT"sv;
				case VK_FORMAT_R8G8B8_SINT: return "VK_FORMAT_R8G8B8_SINT"sv;
				case VK_FORMAT_R8G8B8_SRGB: return "VK_FORMAT_R8G8B8_SRGB"sv;
				case VK_FORMAT_B8G8R8_UNORM: return "VK_FORMAT_B8G8R8_UNORM"sv;
				case VK_FORMAT_B8G8R8_SNORM: return "VK_FORMAT_B8G8R8_SNORM"sv;
				case VK_FORMAT_B8G8R8_USCALED: return "VK_FORMAT_B8G8R8_USCALED"sv;
				case VK_FORMAT_B8G8R8_SSCALED: return "VK_FORMAT_B8G8R8_SSCALED"sv;
				case VK_FORMAT_B8G8R8_UINT: return "VK_FORMAT_B8G8R8_UINT"sv;
				case VK_FORMAT_B8G8R8_SINT: return "VK_FORMAT_B8G8R8_SINT"sv;
				case VK_FORMAT_B8G8R8_SRGB: return "VK_FORMAT_B8G8R8_SRGB"sv;
				case VK_FORMAT_R8G8B8A8_UNORM: return "VK_FORMAT_R8G8B8A8_UNORM"sv;
				case VK_FORMAT_R8G8B8A8_SNORM: return "VK_FORMAT_R8G8B8A8_SNORM"sv;
				case VK_FORMAT_R8G8B8A8_USCALED: return "VK_FORMAT_R8G8B8A8_USCALED"sv;
				case VK_FORMAT_R8G8B8A8_SSCALED: return "VK_FORMAT_R8G8B8A8_SSCALED"sv;
				case VK_FORMAT_R8G8B8A8_UINT: return "VK_FORMAT_R8G8B8A8_UINT"sv;
				case VK_FORMAT_R8G8B8A8_SINT: return "VK_FORMAT_R8G8B8A8_SINT"sv;
				case VK_FORMAT_R8G8B8A8_SRGB: return "VK_FORMAT_R8G8B8A8_SRGB"sv;
				case VK_FORMAT_B8G8R8A8_UNORM: return "VK_FORMAT_B8G8R8A8_UNORM"sv;
				case VK_FORMAT_B8G8R8A8_SNORM: return "VK_FORMAT_B8G8R8A8_SNORM"sv;
				case VK_FORMAT_B8G8R8A8_USCALED: return "VK_FORMAT_B8G8R8A8_USCALED"sv;
				case VK_FORMAT_B8G8R8A8_SSCALED: return "VK_FORMAT_B8G8R8A8_SSCALED"sv;
				case VK_FORMAT_B8G8R8A8_UINT: return "VK_FORMAT_B8G8R8A8_UINT"sv;
				case VK_FORMAT_B8G8R8A8_SINT: return "VK_FORMAT_B8G8R8A8_SINT"sv;
				case VK_FORMAT_B8G8R8A8_SRGB: return "VK_FORMAT_B8G8R8A8_SRGB"sv;
				case VK_FORMAT_A8B8G8R8_UNORM_PACK32: return "VK_FORMAT_A8B8G8R8_UNORM_PACK32"sv;
				case VK_FORMAT_A8B8G8R8_SNORM_PACK32: return "VK_FORMAT_A8B8G8R8_SNORM_PACK32"sv;
				case VK_FORMAT_A8B8G8R8_USCALED_PACK32: return "VK_FORMAT_A8B8G8R8_USCALED_PACK32"sv;
				case VK_FORMAT_A8B8G8R8_SSCALED_PACK32: return "VK_FORMAT_A8B8G8R8_SSCALED_PACK32"sv;
				case VK_FORMAT_A8B8G8R8_UINT_PACK32: return "VK_FORMAT_A8B8G8R8_UINT_PACK32"sv;
				case VK_FORMAT_A8B8G8R8_SINT_PACK32: return "VK_FORMAT_A8B8G8R8_SINT_PACK32"sv;
				case VK_FORMAT_A8B8G8R8_SRGB_PACK32: return "VK_FORMAT_A8B8G8R8_SRGB_PACK32"sv;
				case VK_FORMAT_A2R10G10B10_UNORM_PACK32: return "VK_FORMAT_A2R10G10B10_UNORM_PACK32"sv;
				case VK_FORMAT_A2R10G10B10_SNORM_PACK32: return "VK_FORMAT_A2R10G10B10_SNORM_PACK32"sv;
				case VK_FORMAT_A2R10G10B10_USCALED_PACK32: return "VK_FORMAT_A2R10G10B10_USCALED_PACK32"sv;
				case VK_FORMAT_A2R10G10B10_SSCALED_PACK32: return "VK_FORMAT_A2R10G10B10_SSCALED_PACK32"sv;
				case VK_FORMAT_A2R10G10B10_UINT_PACK32: return "VK_FORMAT_A2R10G10B10_UINT_PACK32"sv;
				case VK_FORMAT_A2R10G10B10_SINT_PACK32: return "VK_FORMAT_A2R10G10B10_SINT_PACK32"sv;
				case VK_FORMAT_A2B10G10R10_UNORM_PACK32: return "VK_FORMAT_A2B10G10R10_UNORM_PACK32"sv;
				case VK_FORMAT_A2B10G10R10_SNORM_PACK32: return "VK_FORMAT_A2B10G10R10_SNORM_PACK32"sv;
				case VK_FORMAT_A2B10G10R10_USCALED_PACK32: return "VK_FORMAT_A2B10G10R10_USCALED_PACK32"sv;
				case VK_FORMAT_A2B10G10R10_SSCALED_PACK32: return "VK_FORMAT_A2B10G10R10_SSCALED_PACK32"sv;
				case VK_FORMAT_A2B10G10R10_UINT_PACK32: return "VK_FORMAT_A2B10G10R10_UINT_PACK32"sv;
				case VK_FORMAT_A2B10G10R10_SINT_PACK32: return "VK_FORMAT_A2B10G10R10_SINT_PACK32"sv;
				case VK_FORMAT_R16_UNORM: return "VK_FORMAT_R16_UNORM"sv;
				case VK_FORMAT_R16_SNORM: return "VK_FORMAT_R16_SNORM"sv;
				case VK_FORMAT_R16_USCALED: return "VK_FORMAT_R16_USCALED"sv;
				case VK_FORMAT_R16_SSCALED: return "VK_FORMAT_R16_SSCALED"sv;
				case VK_FORMAT_R16_UINT: return "VK_FORMAT_R16_UINT"sv;
				case VK_FORMAT_R16_SINT: return "VK_FORMAT_R16_SINT"sv;
				case VK_FORMAT_R16_SFLOAT: return "VK_FORMAT_R16_SFLOAT"sv;
				case VK_FORMAT_R16G16_UNORM: return "VK_FORMAT_R16G16_UNORM"sv;
				case VK_FORMAT_R16G16_SNORM: return "VK_FORMAT_R16G16_SNORM"sv;
				case VK_FORMAT_R16G16_USCALED: return "VK_FORMAT_R16G16_USCALED"sv;
				case VK_FORMAT_R16G16_SSCALED: return "VK_FORMAT_R16G16_SSCALED"sv;
				case VK_FORMAT_R16G16_UINT: return "VK_FORMAT_R16G16_UINT"sv;
				case VK_FORMAT_R16G16_SINT: return "VK_FORMAT_R16G16_SINT"sv;
				case VK_FORMAT_R16G16_SFLOAT: return "VK_FORMAT_R16G16_SFLOAT"sv;
				case VK_FORMAT_R16G16B16_UNORM: return "VK_FORMAT_R16G16B16_UNORM"sv;
				case VK_FORMAT_R16G16B16_SNORM: return "VK_FORMAT_R16G16B16_SNORM"sv;
				case VK_FORMAT_R16G16B16_USCALED: return "VK_FORMAT_R16G16B16_USCALED"sv;
				case VK_FORMAT_R16G16B16_SSCALED: return "VK_FORMAT_R16G16B16_SSCALED"sv;
				case VK_FORMAT_R16G16B16_UINT: return "VK_FORMAT_R16G16B16_UINT"sv;
				case VK_FORMAT_R16G16B16_SINT: return "VK_FORMAT_R16G16B16_SINT"sv;
				case VK_FORMAT_R16G16B16_SFLOAT: return "VK_FORMAT_R16G16B16_SFLOAT"sv;
				case VK_FORMAT_R16G16B16A16_UNORM: return "VK_FORMAT_R16G16B16A16_UNORM"sv;
				case VK_FORMAT_R16G16B16A16_SNORM: return "VK_FORMAT_R16G16B16A16_SNORM"sv;
				case VK_FORMAT_R16G16B16A16_USCALED: return "VK_FORMAT_R16G16B16A16_USCALED"sv;
				case VK_FORMAT_R16G16B16A16_SSCALED: return "VK_FORMAT_R16G16B16A16_SSCALED"sv;
				case VK_FORMAT_R16G16B16A16_UINT: return "VK_FORMAT_R16G16B16A16_UINT"sv;
				case VK_FORMAT_R16G16B16A16_SINT: return "VK_FORMAT_R16G16B16A16_SINT"sv;
				case VK_FORMAT_R16G16B16A16_SFLOAT: return "VK_FORMAT_R16G16B16A16_SFLOAT"sv;
				case VK_FORMAT_R32_UINT: return "VK_FORMAT_R32_UINT"sv;
				case VK_FORMAT_R32_SINT: return "VK_FORMAT_R32_SINT"sv;
				case VK_FORMAT_R32_SFLOAT: return "VK_FORMAT_R32_SFLOAT"sv;
				case VK_FORMAT_R32G32_UINT: return "VK_FORMAT_R32G32_UINT"sv;
				case VK_FORMAT_R32G32_SINT: return "VK_FORMAT_R32G32_SINT"sv;
				case VK_FORMAT_R32G32_SFLOAT: return "VK_FORMAT_R32G32_SFLOAT"sv;
				case VK_FORMAT_R32G32B32_UINT: return "VK_FORMAT_R32G32B32_UINT"sv;
				case VK_FORMAT_R32G32B32_SINT: return "VK_FORMAT_R32G32B32_SINT"sv;
				case VK_FORMAT_R32G32B32_SFLOAT: return "VK_FORMAT_R32G32B32_SFLOAT"sv;
				case VK_FORMAT_R32G32B32A32_UINT: return "VK_FORMAT_R32G32B32A32_UINT"sv;
				case VK_FORMAT_R32G32B32A32_SINT: return "VK_FORMAT_R32G32B32A32_SINT"sv;
				case VK_FORMAT_R32G32B32A32_SFLOAT: return "VK_FORMAT_R32G32B32A32_SFLOAT"sv;
				case VK_FORMAT_R64_UINT: return "VK_FORMAT_R64_UINT"sv;
				case VK_FORMAT_R64_SINT: return "VK_FORMAT_R64_SINT"sv;
				case VK_FORMAT_R64_SFLOAT: return "VK_FORMAT_R64_SFLOAT"sv;
				case VK_FORMAT_R64G64_UINT: return "VK_FORMAT_R64G64_UINT"sv;
				case VK_FORMAT_R64G64_SINT: return "VK_FORMAT_R64G64_SINT"sv;
				case VK_FORMAT_R64G64_SFLOAT: return "VK_FORMAT_R64G64_SFLOAT"sv;
				case VK_FORMAT_R64G64B64_UINT: return "VK_FORMAT_R64G64B64_UINT"sv;
				case VK_FORMAT_R64G64B64_SINT: return "VK_FORMAT_R64G64B64_SINT"sv;
				case VK_FORMAT_R64G64B64_SFLOAT: return "VK_FORMAT_R64G64B64_SFLOAT"sv;
				case VK_FORMAT_R64G64B64A64_UINT: return "VK_FORMAT_R64G64B64A64_UINT"sv;
				case VK_FORMAT_R64G64B64A64_SINT: return "VK_FORMAT_R64G64B64A64_SINT"sv;
				case VK_FORMAT_R64G64B64A64_SFLOAT: return "VK_FORMAT_R64G64B64A64_SFLOAT"sv;
				case VK_FORMAT_B10G11R11_UFLOAT_PACK32: return "VK_FORMAT_B10G11R11_UFLOAT_PACK32"sv;
				case VK_FORMAT_E5B9G9R9_UFLOAT_PACK32: return "VK_FORMAT_E5B9G9R9_UFLOAT_PACK32"sv;
				case VK_FORMAT_D16_UNORM: return "VK_FORMAT_D16_UNORM"sv;
				case VK_FORMAT_X8_D24_UNORM_PACK32: return "VK_FORMAT_X8_D24_UNORM_PACK32"sv;
				case VK_FORMAT_D32_SFLOAT: return "VK_FORMAT_D32_SFLOAT"sv;
				case VK_FORMAT_S8_UINT: return "VK_FORMAT_S8_UINT"sv;
				case VK_FORMAT_D16_UNORM_S8_UINT: return "VK_FORMAT_D16_UNORM_S8_UINT"sv;
				case VK_FORMAT_D24_UNORM_S8_UINT: return "VK_FORMAT_D24_UNORM_S8_UINT"sv;
				case VK_FORMAT_D32_SFLOAT_S8_UINT: return "VK_FORMAT_D32_SFLOAT_S8_UINT"sv;
				case VK_FORMAT_BC1_RGB_UNORM_BLOCK: return "VK_FORMAT_BC1_RGB_UNORM_BLOCK"sv;
				case VK_FORMAT_BC1_RGB_SRGB_BLOCK: return "VK_FORMAT_BC1_RGB_SRGB_BLOCK"sv;
				case VK_FORMAT_BC1_RGBA_UNORM_BLOCK: return "VK_FORMAT_BC1_RGBA_UNORM_BLOCK"sv;
				case VK_FORMAT_BC1_RGBA_SRGB_BLOCK: return "VK_FORMAT_BC1_RGBA_SRGB_BLOCK"sv;
				case VK_FORMAT_BC2_UNORM_BLOCK: return "VK_FORMAT_BC2_UNORM_BLOCK"sv;
				case VK_FORMAT_BC2_SRGB_BLOCK: return "VK_FORMAT_BC2_SRGB_BLOCK"sv;
				case VK_FORMAT_BC3_UNORM_BLOCK: return "VK_FORMAT_BC3_UNORM_BLOCK"sv;
				case VK_FORMAT_BC3_SRGB_BLOCK: return "VK_FORMAT_BC3_SRGB_BLOCK"sv;
				case VK_FORMAT_BC4_UNORM_BLOCK: return "VK_FORMAT_BC4_UNORM_BLOCK"sv;
				case VK_FORMAT_BC4_SNORM_BLOCK: return "VK_FORMAT_BC4_SNORM_BLOCK"sv;
				case VK_FORMAT_BC5_UNORM_BLOCK: return "VK_FORMAT_BC5_UNORM_BLOCK"sv;
				case VK_FORMAT_BC5_SNORM_BLOCK: return "VK_FORMAT_BC5_SNORM_BLOCK"sv;
				case VK_FORMAT_BC6H_UFLOAT_BLOCK: return "VK_FORMAT_BC6H_UFLOAT_BLOCK"sv;
				case VK_FORMAT_BC6H_SFLOAT_BLOCK: return "VK_FORMAT_BC6H_SFLOAT_BLOCK"sv;
				case VK_FORMAT_BC7_UNORM_BLOCK: return "VK_FORMAT_BC7_UNORM_BLOCK"sv;
				case VK_FORMAT_BC7_SRGB_BLOCK: return "VK_FORMAT_BC7_SRGB_BLOCK"sv;
				case VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK: return "VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK"sv;
				case VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK: return "VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK"sv;
				case VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK: return "VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK"sv;
				case VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK: return "VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK"sv;
				case VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK: return "VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK"sv;
				case VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK: return "VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK"sv;
				case VK_FORMAT_EAC_R11_UNORM_BLOCK: return "VK_FORMAT_EAC_R11_UNORM_BLOCK"sv;
				case VK_FORMAT_EAC_R11_SNORM_BLOCK: return "VK_FORMAT_EAC_R11_SNORM_BLOCK"sv;
				case VK_FORMAT_EAC_R11G11_UNORM_BLOCK: return "VK_FORMAT_EAC_R11G11_UNORM_BLOCK"sv;
				case VK_FORMAT_EAC_R11G11_SNORM_BLOCK: return "VK_FORMAT_EAC_R11G11_SNORM_BLOCK"sv;
				case VK_FORMAT_ASTC_4x4_UNORM_BLOCK: return "VK_FORMAT_ASTC_4x4_UNORM_BLOCK"sv;
				case VK_FORMAT_ASTC_4x4_SRGB_BLOCK: return "VK_FORMAT_ASTC_4x4_SRGB_BLOCK"sv;
				case VK_FORMAT_ASTC_5x4_UNORM_BLOCK: return "VK_FORMAT_ASTC_5x4_UNORM_BLOCK"sv;
				case VK_FORMAT_ASTC_5x4_SRGB_BLOCK: return "VK_FORMAT_ASTC_5x4_SRGB_BLOCK"sv;
				case VK_FORMAT_ASTC_5x5_UNORM_BLOCK: return "VK_FORMAT_ASTC_5x5_UNORM_BLOCK"sv;
				case VK_FORMAT_ASTC_5x5_SRGB_BLOCK: return "VK_FORMAT_ASTC_5x5_SRGB_BLOCK"sv;
				case VK_FORMAT_ASTC_6x5_UNORM_BLOCK: return "VK_FORMAT_ASTC_6x5_UNORM_BLOCK"sv;
				case VK_FORMAT_ASTC_6x5_SRGB_BLOCK: return "VK_FORMAT_ASTC_6x5_SRGB_BLOCK"sv;
				case VK_FORMAT_ASTC_6x6_UNORM_BLOCK: return "VK_FORMAT_ASTC_6x6_UNORM_BLOCK"sv;
				case VK_FORMAT_ASTC_6x6_SRGB_BLOCK: return "VK_FORMAT_ASTC_6x6_SRGB_BLOCK"sv;
				case VK_FORMAT_ASTC_8x5_UNORM_BLOCK: return "VK_FORMAT_ASTC_8x5_UNORM_BLOCK"sv;
				case VK_FORMAT_ASTC_8x5_SRGB_BLOCK: return "VK_FORMAT_ASTC_8x5_SRGB_BLOCK"sv;
				case VK_FORMAT_ASTC_8x6_UNORM_BLOCK: return "VK_FORMAT_ASTC_8x6_UNORM_BLOCK"sv;
				case VK_FORMAT_ASTC_8x6_SRGB_BLOCK: return "VK_FORMAT_ASTC_8x6_SRGB_BLOCK"sv;
				case VK_FORMAT_ASTC_8x8_UNORM_BLOCK: return "VK_FORMAT_ASTC_8x8_UNORM_BLOCK"sv;
				case VK_FORMAT_ASTC_8x8_SRGB_BLOCK: return "VK_FORMAT_ASTC_8x8_SRGB_BLOCK"sv;
				case VK_FORMAT_ASTC_10x5_UNORM_BLOCK: return "VK_FORMAT_ASTC_10x5_UNORM_BLOCK"sv;
				case VK_FORMAT_ASTC_10x5_SRGB_BLOCK: return "VK_FORMAT_ASTC_10x5_SRGB_BLOCK"sv;
				case VK_FORMAT_ASTC_10x6_UNORM_BLOCK: return "VK_FORMAT_ASTC_10x6_UNORM_BLOCK"sv;
				case VK_FORMAT_ASTC_10x6_SRGB_BLOCK: return "VK_FORMAT_ASTC_10x6_SRGB_BLOCK"sv;
				case VK_FORMAT_ASTC_10x8_UNORM_BLOCK: return "VK_FORMAT_ASTC_10x8_UNORM_BLOCK"sv;
				case VK_FORMAT_ASTC_10x8_SRGB_BLOCK: return "VK_FORMAT_ASTC_10x8_SRGB_BLOCK"sv;
				case VK_FORMAT_ASTC_10x10_UNORM_BLOCK: return "VK_FORMAT_ASTC_10x10_UNORM_BLOCK"sv;
				case VK_FORMAT_ASTC_10x10_SRGB_BLOCK: return "VK_FORMAT_ASTC_10x10_SRGB_BLOCK"sv;
				case VK_FORMAT_ASTC_12x10_UNORM_BLOCK: return "VK_FORMAT_ASTC_12x10_UNORM_BLOCK"sv;
				case VK_FORMAT_ASTC_12x10_SRGB_BLOCK: return "VK_FORMAT_ASTC_12x10_SRGB_BLOCK"sv;
				case VK_FORMAT_ASTC_12x12_UNORM_BLOCK: return "VK_FORMAT_ASTC_12x12_UNORM_BLOCK"sv;
				case VK_FORMAT_ASTC_12x12_SRGB_BLOCK: return "VK_FORMAT_ASTC_12x12_SRGB_BLOCK"sv;
				case VK_FORMAT_G8B8G8R8_422_UNORM: return "VK_FORMAT_G8B8G8R8_422_UNORM"sv;
				case VK_FORMAT_B8G8R8G8_422_UNORM: return "VK_FORMAT_B8G8R8G8_422_UNORM"sv;
				case VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM: return "VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM"sv;
				case VK_FORMAT_G8_B8R8_2PLANE_420_UNORM: return "VK_FORMAT_G8_B8R8_2PLANE_420_UNORM"sv;
				case VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM: return "VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM"sv;
				case VK_FORMAT_G8_B8R8_2PLANE_422_UNORM: return "VK_FORMAT_G8_B8R8_2PLANE_422_UNORM"sv;
				case VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM: return "VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM"sv;
				case VK_FORMAT_R10X6_UNORM_PACK16: return "VK_FORMAT_R10X6_UNORM_PACK16"sv;
				case VK_FORMAT_R10X6G10X6_UNORM_2PACK16: return "VK_FORMAT_R10X6G10X6_UNORM_2PACK16"sv;
				case VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16: return "VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16"sv;
				case VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16: return "VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16"sv;
				case VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16: return "VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16"sv;
				case VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16: return "VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16"sv;
				case VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16: return "VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16"sv;
				case VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16: return "VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16"sv;
				case VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16: return "VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16"sv;
				case VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16: return "VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16"sv;
				case VK_FORMAT_R12X4_UNORM_PACK16: return "VK_FORMAT_R12X4_UNORM_PACK16"sv;
				case VK_FORMAT_R12X4G12X4_UNORM_2PACK16: return "VK_FORMAT_R12X4G12X4_UNORM_2PACK16"sv;
				case VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16: return "VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16"sv;
				case VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16: return "VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16"sv;
				case VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16: return "VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16"sv;
				case VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16: return "VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16"sv;
				case VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16: return "VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16"sv;
				case VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16: return "VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16"sv;
				case VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16: return "VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16"sv;
				case VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16: return "VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16"sv;
				case VK_FORMAT_G16B16G16R16_422_UNORM: return "VK_FORMAT_G16B16G16R16_422_UNORM"sv;
				case VK_FORMAT_B16G16R16G16_422_UNORM: return "VK_FORMAT_B16G16R16G16_422_UNORM"sv;
				case VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM: return "VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM"sv;
				case VK_FORMAT_G16_B16R16_2PLANE_420_UNORM: return "VK_FORMAT_G16_B16R16_2PLANE_420_UNORM"sv;
				case VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM: return "VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM"sv;
				case VK_FORMAT_G16_B16R16_2PLANE_422_UNORM: return "VK_FORMAT_G16_B16R16_2PLANE_422_UNORM"sv;
				case VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM: return "VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM"sv;
				case VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG: return "VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG"sv;
				case VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG: return "VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG"sv;
				case VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG: return "VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG"sv;
				case VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG: return "VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG"sv;
				case VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG: return "VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG"sv;
				case VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG: return "VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG"sv;
				case VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG: return "VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG"sv;
				case VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG: return "VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG"sv;
				case VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK_EXT: return "VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK_EXT"sv;
				case VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK_EXT: return "VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK_EXT"sv;
				case VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK_EXT: return "VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK_EXT"sv;
				case VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK_EXT: return "VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK_EXT"sv;
				case VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK_EXT: return "VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK_EXT"sv;
				case VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK_EXT: return "VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK_EXT"sv;
				case VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK_EXT: return "VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK_EXT"sv;
				case VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK_EXT: return "VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK_EXT"sv;
				case VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK_EXT: return "VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK_EXT"sv;
				case VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK_EXT: return "VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK_EXT"sv;
				case VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK_EXT: return "VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK_EXT"sv;
				case VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK_EXT: return "VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK_EXT"sv;
				case VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK_EXT: return "VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK_EXT"sv;
				case VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK_EXT: return "VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK_EXT"sv;
				case VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT: return "VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT"sv;
				case VK_FORMAT_A4B4G4R4_UNORM_PACK16_EXT: return "VK_FORMAT_A4B4G4R4_UNORM_PACK16_EXT"sv;
				default:
					spdlog::warn("Unknown {}: {}", "VkFormat", static_cast<u32>(format));
					return "UNKNOWN"sv;
			}
		}
	}

	namespace ColorSpace {
		std::string_view ToString(VkColorSpaceKHR colorSpace) noexcept {
			switch(colorSpace) {
				case VK_COLOR_SPACE_SRGB_NONLINEAR_KHR: return "VK_COLOR_SPACE_SRGB_NONLINEAR_KHR"sv;
				case VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT: return "VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT"sv;
				case VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT: return "VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT"sv;
				case VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT: return "VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT"sv;
				case VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT: return "VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT"sv;
				case VK_COLOR_SPACE_BT709_LINEAR_EXT: return "VK_COLOR_SPACE_BT709_LINEAR_EXT"sv;
				case VK_COLOR_SPACE_BT709_NONLINEAR_EXT: return "VK_COLOR_SPACE_BT709_NONLINEAR_EXT"sv;
				case VK_COLOR_SPACE_BT2020_LINEAR_EXT: return "VK_COLOR_SPACE_BT2020_LINEAR_EXT"sv;
				case VK_COLOR_SPACE_HDR10_ST2084_EXT: return "VK_COLOR_SPACE_HDR10_ST2084_EXT"sv;
				case VK_COLOR_SPACE_DOLBYVISION_EXT: return "VK_COLOR_SPACE_DOLBYVISION_EXT"sv;
				case VK_COLOR_SPACE_HDR10_HLG_EXT: return "VK_COLOR_SPACE_HDR10_HLG_EXT"sv;
				case VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT: return "VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT"sv;
				case VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT: return "VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT"sv;
				case VK_COLOR_SPACE_PASS_THROUGH_EXT: return "VK_COLOR_SPACE_PASS_THROUGH_EXT"sv;
				case VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT: return "VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT"sv;
				case VK_COLOR_SPACE_DISPLAY_NATIVE_AMD: return "VK_COLOR_SPACE_DISPLAY_NATIVE_AMD"sv;
				default:
					spdlog::warn("Invalid {}: {}", "VkColorSpaceKHR", static_cast<u32>(colorSpace));
					return "UNKNOWN"sv;
			}
		}
	}
}
//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanDebugUtils.cpp
//------------------------------------------------------------

#include "VulkanDebugUtils.hpp"
#include "VulkanInstance.hpp"
#include "Util/VulkanUtils.hpp"
#include "Util/VulkanTypes.hpp"
#include <spdlog/spdlog.h>
#include <sstream>

namespace KMLEngine::Vulkan {
	static VkBool32 DebugMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void* userData) {
		const auto logLevel = Types::MessageSeverity::ToLogLevel(messageSeverity);
		const auto name = Types::MessageSeverity::ToString(messageSeverity);

		std::stringstream stream;
		stream << callbackData->pMessageIdName << '(' << name << " / SPEC): msgNum: " << callbackData->messageIdNumber << ' ' << callbackData->pMessage;
		stream << "\n\tObjects: " << callbackData->objectCount;

		for (usize ix = 0; ix < callbackData->objectCount; ix++) {
			const auto& object = callbackData->pObjects[ix];
			const auto typeName = Types::ObjectType::ToString(object.objectType);
			stream << "\n\t\t[" << ix << "] " << std::hex << object.objectHandle << ", type: " << typeName << ", name: " << (object.pObjectName ? object.pObjectName : "NULL");
		}

		spdlog::log(logLevel, stream.str());

		return VK_FALSE;
	}

	void DebugUtils::OnDisposing() {
		vkDestroyDebugUtilsMessengerEXT(m_instance->GetHandle(), m_handle, GetAllocator());
		m_handle = VK_NULL_HANDLE;
		
		m_instance = nullptr;
	}

	void DebugUtils::Create(Instance& instance) {
		m_instance = &instance;

		const auto debugUtilsMessengerCreateInfo = Utils::DebugUtilsMessengerCreateInfoEXT(VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
		                                                                                   VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT, DebugMessengerCallback);
		ThrowIfNotSucceeded(vkCreateDebugUtilsMessengerEXT(instance, &debugUtilsMessengerCreateInfo, GetAllocator(), &m_handle), "vkCreateDebugUtilsMessengerEXT");

		SetInitialized();
	}
}

//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Vulkan.cpp
//------------------------------------------------------------

#include "Vulkan.hpp"
#include "VulkanTypes.hpp"
#include <fmt/format.h>

namespace KMLEngine::Vulkan {
    ResultException::ResultException(const char* functionName, VkResult result) noexcept :
        Exception(fmt::format("{} returned {}", functionName, Types::Result::ToString(result))), m_result(result) {
    }
	
    namespace Loader {
        void Load() {
            if(const auto result = volkInitialize(); result != VK_SUCCESS) ThrowIfFailed(result, "Vulkan::Load");
        }
	
        void Unload() {}
	
        void LoadInstance(VkInstance instance) noexcept {
            KML_ASSERT(instance);
            volkLoadInstance(instance);
        }
	
        void LoadDevice(VkDevice device) noexcept {
            KML_ASSERT(device);
            volkLoadDevice(device);
        }
    }
	
    void ThrowIfNotSucceeded(VkResult result, const char* message) {
        KML_ASSERT(message);

        if(result != VK_SUCCESS) throw ResultException(message, result);
    }
	
    void ThrowIfFailed(VkResult result, const char* message) {
        KML_ASSERT(message);

        if(result < 0) throw ResultException(message, result);
    }
}

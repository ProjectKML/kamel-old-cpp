//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Vulkan.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_VULKAN_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_VULKAN_HPP

#pragma once

#include "../../../../Platform/Types.hpp"
#include "../../../../Platform/Hints/ForceInline.hpp"
#include "../../../../Platform/Assert/Assert.hpp"

#include <volk/volk.h>
#include <vk_mem_alloc/vk_mem_alloc.h>
#include <stdexcept>

namespace KMLEngine::Vulkan {
    class Exception : public std::runtime_error {
    public:
        explicit Exception(const char* message) noexcept : std::runtime_error(message) { KML_ASSERT(message); }
        explicit Exception(const std::string& message) noexcept : std::runtime_error(message) {}
    };

    class ResultException final : public Exception {
    private:
        VkResult m_result;
    public:
        ResultException(const char* functionName, VkResult result) noexcept;

        [[nodiscard]] KML_FORCEINLINE VkResult GetResult() const noexcept { return m_result; }
    };

    namespace Loader {
        void Load();
        void Unload();

        void LoadInstance(VkInstance instance) noexcept;
        void LoadDevice(VkDevice device) noexcept;
    }

    void ThrowIfNotSucceeded(VkResult result, const char* message);
    void ThrowIfFailed(VkResult result, const char* message);

    inline const VkAllocationCallbacks* GetAllocator() noexcept { return nullptr; }
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_VULKAN_HPP

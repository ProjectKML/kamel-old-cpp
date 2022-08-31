//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: VulkanTypes.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_VULKANTYPES_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_VULKANTYPES_HPP

#pragma once

#include "Vulkan.hpp"
#include <spdlog/spdlog.h>

namespace KMLEngine::Vulkan::Types {
    namespace Result {
        std::string_view ToString(VkResult result) noexcept;
    }

    namespace ObjectType {
        std::string_view ToString(VkObjectType objectType) noexcept;
    }

    namespace MessageSeverity {
        spdlog::level::level_enum ToLogLevel(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity) noexcept;
        std::string_view ToString(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity) noexcept;
    }

    namespace PresentMode {
        std::string_view ToString(VkPresentModeKHR presentMode) noexcept;
    }

    namespace Format {
        std::string_view ToString(VkFormat format) noexcept;
    }

    namespace ColorSpace {
        std::string_view ToString(VkColorSpaceKHR colorSpace) noexcept;
    }

    namespace DescriptorType {
        template<VkDescriptorType DescriptorType>
        struct Dynamic {
            static const VkDescriptorType Type = VK_DESCRIPTOR_TYPE_MAX_ENUM;
            static const bool HasDynamic = false;
        };

        template<>
        struct Dynamic<VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER> {
            static const VkDescriptorType Type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
            static const bool HasDynamic = true;
        };

        template<>
        struct Dynamic<VK_DESCRIPTOR_TYPE_STORAGE_BUFFER> {
            static const VkDescriptorType Type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
            static const bool HasDynamic = true;
        };
    }
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_VULKANTYPES_HPP
//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: SpirVUtils.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_SPIRV_SPIRVUTILS_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_SPIRV_SPIRVUTILS_HPP

#pragma once

#include "../Vulkan.hpp"
#include <spirv_cross/spirv.hpp>

namespace KMLEngine::SpirV::Utils {
    namespace ExecutionModel {
        VkShaderStageFlagBits ToShaderStage(spv::ExecutionModel executionModel);
    }
}
#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_SPIRV_SPIRVUTILS_HPP
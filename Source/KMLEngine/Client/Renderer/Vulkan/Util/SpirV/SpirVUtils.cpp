//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: SpirVUtils.cpp
//------------------------------------------------------------

#include "SpirVUtils.hpp"
#include <fmt/format.h>

namespace KMLEngine::SpirV::Utils {
    namespace ExecutionModel {
        VkShaderStageFlagBits ToShaderStage(spv::ExecutionModel executionModel) {
            switch(executionModel) {
                case spv::ExecutionModelVertex:
                    return VK_SHADER_STAGE_VERTEX_BIT;
                case spv::ExecutionModelTessellationControl:
                    return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
                case spv::ExecutionModelTessellationEvaluation:
                    return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
                case spv::ExecutionModelGeometry:
                    return VK_SHADER_STAGE_GEOMETRY_BIT;
                case spv::ExecutionModelFragment:
                    return VK_SHADER_STAGE_FRAGMENT_BIT;
                case spv::ExecutionModelGLCompute:
                case spv::ExecutionModelKernel:
                    return VK_SHADER_STAGE_COMPUTE_BIT; //TODO: VULKAN1.3
                case spv::ExecutionModelTaskNV:
                    return VK_SHADER_STAGE_TASK_BIT_NV;
                case spv::ExecutionModelMeshNV:
                    return VK_SHADER_STAGE_MESH_BIT_NV;
                case spv::ExecutionModelRayGenerationKHR:
                    return VK_SHADER_STAGE_RAYGEN_BIT_KHR;
                case spv::ExecutionModelIntersectionKHR:
                    return VK_SHADER_STAGE_INTERSECTION_BIT_KHR;
                case spv::ExecutionModelAnyHitKHR:
                    return VK_SHADER_STAGE_ANY_HIT_BIT_KHR;
                case spv::ExecutionModelClosestHitKHR:
                    return VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;
                case spv::ExecutionModelMissKHR:
                    return VK_SHADER_STAGE_MISS_BIT_KHR;
                case spv::ExecutionModelCallableKHR:
                    return VK_SHADER_STAGE_CALLABLE_BIT_KHR;
                default:
                    throw Vulkan::Exception(fmt::format("Unknown {}: {}", "spv::ExecutionModel", static_cast<u32>(executionModel)));
            }
        }
    }
}

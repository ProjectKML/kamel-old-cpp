//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: SpirVReflection.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_SPIRV_SPIRVREFLECTION_HPP
#define KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_SPIRV_SPIRVREFLECTION_HPP

#pragma once

#include "../../Pipeline/VulkanPipelineLayout.hpp"
#include "../../../../../Common/Util/STL/btree_map.hpp"
#include "../../../../../Common/Util/STL/btree_set.hpp"
#include "../../../../../Common/Util/STL/flat_hash_set.hpp"

namespace KMLEngine {
    namespace Vulkan { class ShaderModule; }

    namespace SpirV {
        struct ReflectedStages {
            kml_stl::btree_map<Vulkan::DescriptorSetLayout::BindingIndex, Vulkan::DescriptorSetLayout::HashableBindingDesc> Bindings;
            kml_stl::btree_map<u32, Vulkan::PipelineLayout::HashablePushConstantRange> PushConstantRanges;
            kml_stl::flat_hash_set<std::string> DynamicBuffers;
            usize MaxSetIndex = 0;
        };
        
        namespace Reflection {
            void ReflectStages(ReflectedStages& reflectedStages, const kml_stl::btree_set<const Vulkan::ShaderModule*>& shaderModules);
            void GetPipelineLayoutDesc(Vulkan::PipelineLayout::HashableDesc& pipelineLayoutDesc, const ReflectedStages& reflectedStages);
        }
    }
}

#endif //KMLENGINE_CLIENT_RENDERER_VULKAN_UTIL_SPIRV_SPIRVREFLECTION_HPP
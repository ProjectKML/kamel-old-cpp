//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: SpirVReflection.cpp
//------------------------------------------------------------

#include "SpirVReflection.hpp"
#include "../../Pipeline/VulkanShaderModule.hpp"
#include "../../Util/VulkanUtils.hpp"
#include "../../Util/VulkanTypes.hpp"
#include "SpirVUtils.hpp"
#include <spirv_cross/spirv_cross.hpp>
#include <simdjson/simdjson.h>

namespace KMLEngine::SpirV::Reflection {
    static void ReflectCustomProperties(const PackageLocation& location, ReflectedStages& reflectedStages) {
        const auto jsonLocation = location.GetSuffixed(".json");
        if (!jsonLocation.Exists()) return;

        std::string content;
        jsonLocation.GetEntry(content);

        simdjson::dom::parser parser;
        const auto root = parser.parse(content);

        for (const auto& dynamicBuffersJson = root["DynamicBuffers"].get_array(); const auto& dynamicBuffer : dynamicBuffersJson) {
            reflectedStages.DynamicBuffers.insert(std::string(dynamicBuffer.get_string().value()));
        }
    }

    template<VkDescriptorType DescriptorType>
    static void ReflectDescriptors(const spirv_cross::Compiler& compiler,
                                   const spirv_cross::SmallVector<spirv_cross::Resource>& resources,
                                   VkShaderStageFlags moduleFlags,
                                   ReflectedStages& reflectedStages) {
        for(const auto& resource : resources) {
            const Vulkan::DescriptorSetLayout::BindingIndex bindingIndex(compiler.get_decoration(resource.id, spv::DecorationDescriptorSet),
                                                                 compiler.get_decoration(resource.id, spv::DecorationBinding));

            const auto& type = compiler.get_type(resource.type_id);
            const auto descriptorCount = type.array.empty() ? 1 : type.array[0];

            auto& bindings = reflectedStages.Bindings;
            if(auto iterator = bindings.find(bindingIndex); iterator == bindings.end()) {
                auto descriptorType = DescriptorType;

                if constexpr(Vulkan::Types::DescriptorType::Dynamic<DescriptorType>::HasDynamic) {
                    if(reflectedStages.DynamicBuffers.find(resource.name) != reflectedStages.DynamicBuffers.end())
                        descriptorType = Vulkan::Types::DescriptorType::Dynamic<DescriptorType>::Type;
                } else {
                    KML_ASSERT(reflectedStages.DynamicBuffers.find(resource.name) == reflectedStages.DynamicBuffers.end());
                }

                bindings.insert(std::make_pair(bindingIndex, Vulkan::DescriptorSetLayout::HashableBindingDesc(bindingIndex.Binding,
                                                                                                      descriptorType,
                                                                                                      descriptorCount,
                                                                                                      moduleFlags,
                                                                                                      {}))); //TODO: immutable samplers
            } else iterator->second.StageFlags |= moduleFlags;

            if(bindingIndex.Set > reflectedStages.MaxSetIndex) reflectedStages.MaxSetIndex = bindingIndex.Set;
        }
    }

    static void ReflectPushConstants(const spirv_cross::Compiler& compiler,
                                     const spirv_cross::SmallVector<spirv_cross::Resource>& pushConstants,
                                     VkShaderStageFlags moduleFlags,
                                     ReflectedStages& reflectedStages) {
        if(pushConstants.empty()) return;

        KML_ASSERT(pushConstants.size() == 1);

        const auto& pushConstant = pushConstants[0];
        const auto activeRanges = compiler.get_active_buffer_ranges(pushConstant.id);

        for(const auto& activeRange : activeRanges) {
            auto iterator = reflectedStages.PushConstantRanges.find(activeRange.index);
            if(iterator == reflectedStages.PushConstantRanges.end()) {
                reflectedStages.PushConstantRanges.insert(std::make_pair(activeRange.index,
                                                                         Vulkan::PipelineLayout::HashablePushConstantRange(moduleFlags, activeRange.offset, activeRange.range)));
            } else iterator->second.StageFlags |= moduleFlags;
        }
    }

    void ReflectStages(ReflectedStages& reflectedStages, const kml_stl::btree_set<const Vulkan::ShaderModule*>& shaderModules) {
        for(const auto* shaderModule : shaderModules) {
            KML_ASSERT(shaderModule);

            const auto& byteCode = shaderModule->GetByteCode();
            const spirv_cross::Compiler compiler(reinterpret_cast<const u32*>(byteCode.data()), byteCode.size() >> 2);

            const auto entryPoints = compiler.get_entry_points_and_stages();
            VkShaderStageFlags moduleFlags = 0;
            
            //Entry points
            for(const auto& entryPoint : entryPoints) {
                const auto stage = Utils::ExecutionModel::ToShaderStage(entryPoint.execution_model);
                moduleFlags |= stage;
            }

            //Resources
            const auto resources = compiler.get_shader_resources();

            ReflectDescriptors<VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER>(compiler, resources.uniform_buffers, moduleFlags, reflectedStages);
            ReflectDescriptors<VK_DESCRIPTOR_TYPE_STORAGE_BUFFER>(compiler, resources.storage_buffers, moduleFlags, reflectedStages);
            ReflectDescriptors<VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT>(compiler, resources.subpass_inputs, moduleFlags, reflectedStages);
            ReflectDescriptors<VK_DESCRIPTOR_TYPE_STORAGE_IMAGE>(compiler, resources.storage_images, moduleFlags, reflectedStages);
            ReflectDescriptors<VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER>(compiler, resources.sampled_images, moduleFlags, reflectedStages);
            ReflectDescriptors<VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR>(compiler, resources.acceleration_structures, moduleFlags, reflectedStages);
            ReflectDescriptors<VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE>(compiler, resources.separate_images, moduleFlags, reflectedStages);
            ReflectDescriptors<VK_DESCRIPTOR_TYPE_SAMPLER>(compiler, resources.separate_samplers, moduleFlags, reflectedStages);

            ReflectPushConstants(compiler, resources.push_constant_buffers, moduleFlags, reflectedStages);
        }
    }

    void GetPipelineLayoutDesc(Vulkan::PipelineLayout::HashableDesc& pipelineLayoutDesc,
                               const ReflectedStages& reflectedStages) {
        const auto numSets = reflectedStages.MaxSetIndex + 1;
        pipelineLayoutDesc.SetLayouts.resize(numSets);

        for(const auto& [bindingIndex, bindingDesc] : reflectedStages.Bindings) {
            pipelineLayoutDesc.SetLayouts[bindingIndex.Set].Bindings.push_back(bindingDesc); //TODO: Flags & BindingFlags from json
        }

        for(const auto& [index, pushConstantRange] : reflectedStages.PushConstantRanges) {
            pipelineLayoutDesc.PushConstantRanges.push_back(pushConstantRange);
        }
    }
}
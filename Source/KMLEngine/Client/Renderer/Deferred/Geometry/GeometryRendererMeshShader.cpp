//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: GeometryRendererMeshShader.cpp
//------------------------------------------------------------

#include "GeometryRendererMeshShader.hpp"
#include "../GeometryBuffer.hpp"
#include "../../RenderContext.hpp"
#include "../../Common/Frame/RenderFrameResources.hpp"
#include "../../Common/Resources/Model/Obj/ClusterizedObjMesh.hpp"
#include "../../Vulkan/Pipeline/VulkanShaderModule.hpp"

namespace KMLEngine {
    //GeometryRendererMeshShader::Frame
    void GeometryRendererMeshShader::Frame::OnDisposing() {
        m_cameraConstantsDescriptorSet.Dispose();
        m_cameraConstantsUniformBuffer.Dispose();
    }

    void GeometryRendererMeshShader::Frame::Create([[maybe_unused]] RenderFrameResources& currentFrame, RenderContext& context) {
        auto& device = context.GetDevice();

        m_cameraConstantsUniformBuffer.Create(device, sizeof(CameraConstants), VMA_MEMORY_USAGE_CPU_TO_GPU, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);

        {
            Vulkan::DescriptorSet::Builder builder;
            builder.AddBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_MESH_BIT_NV);

            m_cameraConstantsDescriptorSet.Create(device, builder);

            const auto descriptorBufferInfo = Vulkan::Utils::DescriptorBufferInfo(m_cameraConstantsUniformBuffer, m_cameraConstantsUniformBuffer.GetSize()); 
            const auto writeDescriptorSet = Vulkan::Utils::WriteDescriptorSet(m_cameraConstantsDescriptorSet, 0, 0, 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                nullptr, &descriptorBufferInfo);

            m_cameraConstantsDescriptorSet.Update(1, &writeDescriptorSet);
        }

        SetInitialized();
    }

    void GeometryRendererMeshShader::Frame::Update(const Camera& camera) {
        auto* mappedBuffer = m_cameraConstantsUniformBuffer.Map<CameraConstants>();
        
        mappedBuffer->ViewMatrix = camera.GetViewMatrix();
        mappedBuffer->ProjectionMatrix = camera.GetProjectionMatrix();
        mappedBuffer->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
        mappedBuffer->FrustumPlanes = camera.GetFrustumPlanes(); //TODO: map/unmap thing;

        m_cameraConstantsUniformBuffer.Unmap();
    }

    //GeometryRendererMeshShader
    void GeometryRendererMeshShader::RenderStaticGeometry(const RenderFrameResources& currentFrame, Vulkan::CommandBuffer& commandBuffer, const TimerEventArgs& timerEventArgs) {
        m_camera.Update(timerEventArgs); //TODO: pls, not here!
        
        auto& frameData = m_frameCollection.Get(currentFrame);
        frameData.Update(m_camera);
        
        commandBuffer.BindPipeline(m_defaultPipeline);
        commandBuffer.BindDescriptorSet(m_defaultPipeline, frameData.GetCameraConstantsDescriptorSet());
        commandBuffer.BindDescriptorSet(m_defaultPipeline, m_modelDescriptorSet, 1);
        commandBuffer.DrawMeshTasksNV((m_model.GetNumMeshlets() + 31) / 32, 0);
    }

    GeometryRendererMeshShader::GeometryRendererMeshShader(RenderContext& context, GeometryBuffer& geometryBuffer) {
        auto& device = context.GetDevice();

        //Create frame collection
        m_frameCollection.Create(context.GetFrameManager(), context);

        //Create pipeline
        {
            u32 value = 1;
            VkSpecializationMapEntry entry = { 0, 0, sizeof(u32) };
            VkSpecializationInfo info = {1, &entry, sizeof(value), &value };    

            Vulkan::ShaderModule taskShader;
            taskShader.Create(device, PackageLocation("Resources", "geometry_default.task.spv"));
            
            Vulkan::ShaderModule meshShader;
            meshShader.Create(device, PackageLocation("Resources", "geometry_default.mesh.spv"));

            Vulkan::ShaderModule fragmentShader;
            fragmentShader.Create(device, PackageLocation("Resources", "geometry_default.frag.spv"));
            
            Vulkan::GraphicsPipeline::Builder builder;
            builder.AddShaderStage(VK_SHADER_STAGE_TASK_BIT_NV, taskShader, "main")
                .AddShaderStage(VK_SHADER_STAGE_MESH_BIT_NV, meshShader, "main", &info)
                .AddShaderStage(VK_SHADER_STAGE_FRAGMENT_BIT, fragmentShader, "main", &info)
                .SetInputAssemblyState(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST)
                .AddViewport(0.0f, 0.0f, 1.0f, 1.0f)
                .AddScissor(0, 0, 1, 1)
                .SetRasterizationState(VK_POLYGON_MODE_FILL, VK_CULL_MODE_NONE, VK_FRONT_FACE_CLOCKWISE)
                .SetDepthStencilState(VK_TRUE, VK_TRUE, VK_COMPARE_OP_GREATER)
                .SetMultisampleState(VK_SAMPLE_COUNT_1_BIT)
                .SetColorBlendState()
                .AddBlendAttachmentState().AddBlendAttachmentState().AddBlendAttachmentState()
                .AddDynamicState(VK_DYNAMIC_STATE_VIEWPORT)
                .AddDynamicState(VK_DYNAMIC_STATE_SCISSOR)
                .SetRenderPass(geometryBuffer.GetRenderPass());

            m_defaultPipeline.Create(device, builder);

            fragmentShader.Dispose();
            meshShader.Dispose();
            taskShader.Dispose();
        }

        m_model.Load(context, PackageLocation("Resources", "dragon.obj"));

        {
            Vulkan::DescriptorSet::Builder builder;
            for(auto i = 0; i < 3; i++) builder.AddBinding(i, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, VK_SHADER_STAGE_MESH_BIT_NV);
            m_modelDescriptorSet.Create(device, builder);

            std::array<VkDescriptorBufferInfo, 3> descriptorBufferInfos;
            std::array<VkWriteDescriptorSet, 3> writeDescriptorSets;

            descriptorBufferInfos[0] = Vulkan::Utils::DescriptorBufferInfo(m_model.GetVertexBuffer(), m_model.GetVertexBuffer().GetSize());
            descriptorBufferInfos[1] = Vulkan::Utils::DescriptorBufferInfo(m_model.GetMeshletBuffer(), m_model.GetMeshletBuffer().GetSize());
            descriptorBufferInfos[2] = Vulkan::Utils::DescriptorBufferInfo(m_model.GetMeshletDataBuffer(), m_model.GetMeshletDataBuffer().GetSize());

            for(auto i = 0; i < 3; i++) {
                writeDescriptorSets[i] = Vulkan::Utils::WriteDescriptorSet(m_modelDescriptorSet, i, 0, 1, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, nullptr, descriptorBufferInfos.data() + i);
            }

            m_modelDescriptorSet.Update(3, writeDescriptorSets.data());
        }
    }

    GeometryRendererMeshShader::~GeometryRendererMeshShader() {
        m_modelDescriptorSet.Dispose();
        m_model.Dispose();
        
        m_defaultPipeline.Dispose();
        m_frameCollection.Destroy();
    }
}

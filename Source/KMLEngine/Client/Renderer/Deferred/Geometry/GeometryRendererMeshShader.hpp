//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: GeometryRendererMeshShader.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_DEFERRED_GEOMETRY_GEOMETRYRENDERERMESHSHADER_HPP
#define KMLENGINE_CLIENT_RENDERER_DEFERRED_GEOMETRY_GEOMETRYRENDERERMESHSHADER_HPP

#pragma once

#include "GeometryRenderer.hpp"
#include "../../Common/Frame/RenderFrameCollection.hpp"
#include "../../Vulkan/Buffer/VulkanBuffer.hpp"
#include "../../Vulkan/Descriptor/VulkanDescriptorSet.hpp"
#include "../../Vulkan/Pipeline/VulkanGraphicsPipeline.hpp"
#include "../../../Camera/FreeCamera.hpp"
#include "../../Common/Resources/Model/Obj/ClusterizedObjModel.hpp"

namespace KMLEngine {
    class RenderContext;
    class GeometryBuffer;

    class GeometryRendererMeshShader final : public GeometryRenderer {
    public:
        class Frame final : public Disposable<Frame> {
            friend Disposable<Frame>;
        private:
            Vulkan::Buffer m_cameraConstantsUniformBuffer;
            Vulkan::DescriptorSet m_cameraConstantsDescriptorSet;

            struct CameraConstants final { //TODO: alignas?
                glm::mat4 ViewMatrix;
                glm::mat4 ProjectionMatrix;
                glm::mat4 ViewProjectionMatrix;
                std::array<glm::vec4, 6> FrustumPlanes;
            };

            void OnDisposing();
        public:
            void Create(RenderFrameResources& currentFrame, RenderContext& context);
            void Update(const Camera& camera);

            [[nodiscard]] KML_FORCEINLINE Vulkan::Buffer& GetCameraConstantsUniformBuffer() noexcept { return m_cameraConstantsUniformBuffer; }
            [[nodiscard]] KML_FORCEINLINE const Vulkan::Buffer& GetCameraConstantsUniformBuffer() const noexcept { return m_cameraConstantsUniformBuffer; }

            [[nodiscard]] KML_FORCEINLINE Vulkan::DescriptorSet& GetCameraConstantsDescriptorSet() noexcept { return m_cameraConstantsDescriptorSet; }
            [[nodiscard]] KML_FORCEINLINE const Vulkan::DescriptorSet& GetCameraConstantsDescriptorSet() const noexcept { return m_cameraConstantsDescriptorSet; }
        };
    private:
        RenderFrameCollection<Frame> m_frameCollection;
        
        Vulkan::GraphicsPipeline m_defaultPipeline, m_defaultPipelineVisualizeMeshlets, m_defaultPipelineVisualizeTriangles;
        
        ClusterizedObjModel m_model;
        Vulkan::DescriptorSet m_modelDescriptorSet;

        FreeCamera m_camera;
        
        void RenderStaticGeometry(const RenderFrameResources& currentFrame, Vulkan::CommandBuffer& commandBuffer, const TimerEventArgs& timerEventArgs) final;
    public:
        explicit GeometryRendererMeshShader(RenderContext& context, GeometryBuffer& geometryBuffer);
        ~GeometryRendererMeshShader();
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_DEFERRED_GEOMETRY_GEOMETRYRENDERERMESHSHADER_HPP
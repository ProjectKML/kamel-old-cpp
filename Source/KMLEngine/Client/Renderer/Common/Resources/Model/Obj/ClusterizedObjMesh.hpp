//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ClusterizedObjMesh.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_MODEL_OBJ_CLUSTERIZEDOBJMESH_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_MODEL_OBJ_CLUSTERIZEDOBJMESH_HPP

#pragma once

#include "TriangulatedObjMesh.hpp"

namespace KMLEngine {
    class PackageLocation;

    class ClusterizedObjMesh final {
    public:
        struct Meshlet final {
            glm::vec3 Center = glm::vec3(0.0f);
            f32 Radius = 0.0f;

            glm::i8vec4 ConeData = glm::i8vec4(0); //XYZ: Cone Axis, W: Cone Cutoff
            
            u32 DataOffset = 0;
            u8 VertexCount = 0;
            u8 TriangleCount = 0;

            Meshlet() = default;
            Meshlet(const glm::vec3& center, f32 radius, const glm::i8vec4& coneData, u32 dataOffset, u8 vertexCount, u8 triangleCount) noexcept
                : Center(center), Radius(radius), ConeData(coneData), DataOffset(dataOffset), VertexCount(vertexCount), TriangleCount(triangleCount) {
                
            }
        };
    private:
        std::vector<TriangulatedObjMesh::Vertex> m_vertices;
        std::vector<Meshlet> m_meshlets;
        std::vector<u32> m_meshletData;
    public:
        ClusterizedObjMesh() = default;
        explicit ClusterizedObjMesh(const PackageLocation& location) { Load(location); }

        void Load(const PackageLocation& location);

        [[nodiscard]] KML_FORCEINLINE const std::vector<TriangulatedObjMesh::Vertex>& GetVertices() const noexcept { return m_vertices; }
        [[nodiscard]] KML_FORCEINLINE const std::vector<Meshlet>& GetMeshlets() const noexcept { return m_meshlets; }
        [[nodiscard]] KML_FORCEINLINE const std::vector<u32>& GetMeshletData() const noexcept { return m_meshletData; }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_MODEL_OBJ_CLUSTERIZEDOBJMESH_HPP
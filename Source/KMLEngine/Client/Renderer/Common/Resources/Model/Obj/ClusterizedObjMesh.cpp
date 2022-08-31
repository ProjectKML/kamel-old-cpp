//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ClusterizedObjMesh.cpp
//------------------------------------------------------------

#include "ClusterizedObjMesh.hpp"
#include <meshoptimizer/meshoptimizer.h>
#include <spdlog/spdlog.h>

namespace KMLEngine {
    static const usize _MAX_VERTICES = 64;
    static const usize _MAX_TRIANGLES = 124;
    static const f32 _CONE_WEIGHT = 0.0f;

    void ClusterizedObjMesh::Load(const PackageLocation& location) {
        TriangulatedObjMesh triangulateMesh;
        triangulateMesh.Load(location);

        const auto& vertices = triangulateMesh.GetVertices();
        const auto& indices = triangulateMesh.GetIndices();

        const auto maxMeshlets = meshopt_buildMeshletsBound(indices.size(), _MAX_VERTICES, _MAX_TRIANGLES);
        std::vector<meshopt_Meshlet> meshlets(maxMeshlets);

        std::vector<u32> meshletVertices(maxMeshlets * _MAX_VERTICES);
        std::vector<u8> meshletTriangles(maxMeshlets * _MAX_TRIANGLES);

        const auto meshletCount = meshopt_buildMeshlets(meshlets.data(), meshletVertices.data(), meshletTriangles.data(), indices.data(),
            indices.size(), &vertices[0].Position.x, vertices.size(), sizeof(TriangulatedObjMesh::Vertex), _MAX_VERTICES, _MAX_TRIANGLES, _CONE_WEIGHT);

        m_meshlets.resize((meshletCount + 31) & ~31);

        usize numMeshletData = 0;
        for(auto i = 0; i < meshletCount; i++) {
            const auto& meshlet = meshlets[i];

            numMeshletData += meshlet.vertex_count;
            numMeshletData += (meshlet.triangle_count * 3 + 3) / 4;
        }

        m_meshletData.resize(numMeshletData);
        
        usize index = 0;
        
        for(auto i = 0; i < meshletCount; i++) {
            const auto& meshlet = meshlets[i];

            const auto dataOffset = index;

            for(auto j = 0; j < meshlet.vertex_count; j++) m_meshletData[index++] = meshletVertices[meshlet.vertex_offset + j];

            const auto* packedIndices = reinterpret_cast<const u32*>(meshletTriangles.data() + meshlet.triangle_offset);
            const auto numPackedIndices = (meshlet.triangle_count * 3 + 3) / 4;

            for(auto j = 0; j < numPackedIndices; j++) m_meshletData[index++] = packedIndices[j];

            const auto bounds = meshopt_computeMeshletBounds(meshletVertices.data(), meshletTriangles.data(), meshlet.triangle_count, &vertices[0].Position.x,
                vertices.size(), sizeof(TriangulatedObjMesh::Vertex));

            const glm::vec3 center(bounds.center[0], bounds.center[1], bounds.center[2]);
            const glm::i8vec4 coneData(bounds.cone_axis_s8[0], bounds.cone_axis_s8[1], bounds.cone_axis_s8[2], bounds.cone_cutoff_s8);
            
            new (m_meshlets.data() + i) Meshlet(center, bounds.radius, coneData, dataOffset, static_cast<u8>(meshlet.vertex_count), static_cast<u8>(meshlet.triangle_count));
        }
        
        m_vertices = std::move(triangulateMesh.m_vertices);


    }
}

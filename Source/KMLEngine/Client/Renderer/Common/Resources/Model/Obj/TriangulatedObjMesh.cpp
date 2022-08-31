//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: TriangulatedObjMesh.cpp
//------------------------------------------------------------

#include "TriangulatedObjMesh.hpp"
#include "ObjLoader.hpp"
#include "../../../../../../Platform/Assert/Assert.hpp"
#include <meshoptimizer/meshoptimizer.h>

namespace KMLEngine {
    void TriangulatedObjMesh::Load(const PackageLocation& location) {
        KML_ASSERT(m_vertices.empty());
        KML_ASSERT(m_indices.empty());

        auto* mesh = ObjLoader::Load(location);

        usize indexCount = 0;
        for(auto i = 0; i < mesh->face_count; i++) indexCount += 3 * (mesh->face_vertices[i] - 2);

        std::vector<Vertex> triangulatedVertices(indexCount);

        usize vertexOffset = 0, indexOffset = 0;
        for(auto i = 0; i < mesh->face_count; i++) {
            const auto faceVertices = mesh->face_vertices[i];

            for(auto j = 0; j < faceVertices; j++) {
                const auto index = mesh->indices[indexOffset + j];

                if(j >= 3) {
                    triangulatedVertices[vertexOffset] = triangulatedVertices[vertexOffset - 3];
                    triangulatedVertices[vertexOffset + 1] = triangulatedVertices[vertexOffset - 1];
                    vertexOffset += 2;
                }

                auto& vertex = triangulatedVertices[vertexOffset++];

                const auto positionIndex = index.p * 3;
                const auto texCoordIndex = index.t * 2;
                const auto normalIndex = index.n * 3;

                vertex.Position.x = mesh->positions[positionIndex];
                vertex.Position.y = mesh->positions[positionIndex + 1];
                vertex.Position.z = mesh->positions[positionIndex + 2];
                vertex.TexCoord.x = mesh->texcoords[texCoordIndex];
                vertex.TexCoord.y = mesh->texcoords[texCoordIndex + 1];
                vertex.Normal.x = static_cast<u8>(mesh->normals[normalIndex] * 127.0f + 127.5f);
                vertex.Normal.y = static_cast<u8>(mesh->normals[normalIndex + 1] * 127.0f + 127.5f);
                vertex.Normal.z = static_cast<u8>(mesh->normals[normalIndex + 2] * 127.0f + 127.5f);
            }

            indexOffset += faceVertices;
        }

        KML_ASSERT(vertexOffset == indexCount); //TODO:

        ObjLoader::Unload(mesh);

        //Remap
        std::vector<u32> remap(triangulatedVertices.size());
        const auto vertexCount = meshopt_generateVertexRemap(remap.data(), nullptr, indexCount, triangulatedVertices.data(), indexCount, sizeof(Vertex));

        m_vertices.resize(vertexCount);
        m_indices.resize(indexCount);

        meshopt_remapVertexBuffer(m_vertices.data(), triangulatedVertices.data(), indexCount, sizeof(Vertex), remap.data());
        meshopt_remapIndexBuffer(m_indices.data(), nullptr, indexCount, remap.data());

        meshopt_optimizeVertexCache(m_indices.data(), m_indices.data(), indexCount, vertexCount);
        meshopt_optimizeVertexFetch(m_vertices.data(), m_indices.data(), indexCount, m_vertices.data(), vertexCount, sizeof(Vertex));
    }
}
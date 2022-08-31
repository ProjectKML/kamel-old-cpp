//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: TriangulatedObjMesh.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_MODEL_OBJ_TRIANGULATEDOBJMESH_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_MODEL_OBJ_TRIANGULATEDOBJMESH_HPP

#pragma once

#include "../../../../../../Platform/Types.hpp"
#include "../../../../../../Platform/Hints/ForceInline.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace KMLEngine {
    class PackageLocation;

    class TriangulatedObjMesh final {
        friend class ClusterizedObjMesh;
    public:
        struct Vertex final {
            glm::vec3 Position = {};
            glm::vec2 TexCoord = {};
            glm::bvec4 Normal = {};

            Vertex() = default;
            Vertex(const glm::vec3& position, const glm::vec2& texCoord, const glm::bvec4& normal) noexcept
                    : Position(position), TexCoord(texCoord), Normal(normal) {}
        };

    private:
        std::vector<Vertex> m_vertices;
        std::vector<u32> m_indices;
    public:
        TriangulatedObjMesh() = default;
        explicit TriangulatedObjMesh(const PackageLocation& location) { Load(location); }

        void Load(const PackageLocation& location);

        KML_FORCEINLINE void Clear() noexcept {
            m_vertices.clear();
            m_indices.clear();
        }

        [[nodiscard]] KML_FORCEINLINE const std::vector<Vertex>& GetVertices() const noexcept { return m_vertices; }
        [[nodiscard]] KML_FORCEINLINE const std::vector<u32>& GetIndices() const noexcept { return m_indices; }
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_MODEL_OBJ_TRIANGULATEDOBJMESH_HPP
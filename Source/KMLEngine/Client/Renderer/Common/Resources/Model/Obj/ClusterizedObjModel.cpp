//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
//------------------------------------------------------------

#include "ClusterizedObjModel.hpp"
#include "ClusterizedObjMesh.hpp"
#include "../../../../RenderContext.hpp"
#include "../../Upload/ResourceUploader.hpp"

namespace KMLEngine {
    void ClusterizedObjModel::OnDisposing() {
        m_meshletDataBuffer.Dispose();
        m_meshletBuffer.Dispose();
        m_vertexBuffer.Dispose();
    }

    void ClusterizedObjModel::Load(RenderContext& context, const PackageLocation& location) {
        auto& resourceUploader = context.GetResourceUploader();

        ClusterizedObjMesh mesh;
        mesh.Load(location);

        const auto& vertices = mesh.GetVertices();
        resourceUploader.CreateAndUploadBuffer(context, m_vertexBuffer, vertices.data(), vertices.size() * sizeof(TriangulatedObjMesh::Vertex), VK_BUFFER_USAGE_STORAGE_BUFFER_BIT);

        const auto& meshlets = mesh.GetMeshlets();
        resourceUploader.CreateAndUploadBuffer(context, m_meshletBuffer, meshlets.data(), meshlets.size() * sizeof(ClusterizedObjMesh::Meshlet), VK_BUFFER_USAGE_STORAGE_BUFFER_BIT);

        const auto& meshletData = mesh.GetMeshletData();
        resourceUploader.CreateAndUploadBuffer(context, m_meshletDataBuffer, meshletData.data(), meshletData.size() * sizeof(u32), VK_BUFFER_USAGE_STORAGE_BUFFER_BIT);
        
        m_numMeshlets = mesh.GetMeshlets().size(); //TODO: make ~32 thing only affect mem
        
        SetInitialized();
    }
}

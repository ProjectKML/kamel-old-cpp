//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ClusterizedObjModel.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_MODEL_OBJ_CLUSTERIZEDOBJMODEL_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_MODEL_OBJ_CLUSTERIZEDOBJMODEL_HPP

#pragma once

#include "../../../../Vulkan/Buffer/VulkanBuffer.hpp"

namespace KMLEngine {
	class RenderContext;
	class PackageLocation;
	
	class ClusterizedObjModel final : public Disposable<ClusterizedObjModel> {
		friend Disposable<ClusterizedObjModel>;
	private:
		Vulkan::Buffer m_vertexBuffer;
		Vulkan::Buffer m_meshletBuffer;
		Vulkan::Buffer m_meshletDataBuffer;

		u32 m_numMeshlets = 0;
		
		void OnDisposing();
	public:
		void Load(RenderContext& context, const PackageLocation& location);

		[[nodiscard]] KML_FORCEINLINE Vulkan::Buffer& GetVertexBuffer() noexcept { return m_vertexBuffer; }
		[[nodiscard]] KML_FORCEINLINE const Vulkan::Buffer& GetVertexBuffer() const noexcept { return m_vertexBuffer; }

		[[nodiscard]] KML_FORCEINLINE Vulkan::Buffer& GetMeshletBuffer() noexcept { return m_meshletBuffer; }
		[[nodiscard]] KML_FORCEINLINE const Vulkan::Buffer& GetMeshletBuffer() const noexcept { return m_meshletBuffer; }

		[[nodiscard]] KML_FORCEINLINE Vulkan::Buffer& GetMeshletDataBuffer() noexcept { return m_meshletDataBuffer; }
		[[nodiscard]] KML_FORCEINLINE const Vulkan::Buffer& GetMeshletDataBuffer() const noexcept { return m_meshletDataBuffer; }

		[[nodiscard]] KML_FORCEINLINE u32 GetNumMeshlets() const noexcept { return m_numMeshlets; }
	};
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_MODEL_OBJ_CLUSTERIZEDOBJMODEL_HPP
#version 460
#extension GL_ARB_separate_shader_objects : enable
#extension GL_GOOGLE_include_directive : require

#extension GL_EXT_shader_8bit_storage : require

#extension GL_NV_mesh_shader : require

#include "Util/mesh_types.h"
#include "Util/visualization_mode.h"
#include "Util/hash.h"

layout(local_size_x = 32, local_size_y = 1, local_size_z = 1) in;
layout(triangles, max_vertices = MAX_VERTICES, max_primitives = MAX_PRIMITIVES) out;

layout(constant_id = 0) const uint visualizationMode = VISUALIZATION_MODE_NONE;

layout(location = 0) out vec3 colors[];

layout(set = 0, binding = 0) uniform CameraConstants {
	mat4 viewMatrix;
	mat4 projectionMatrix;
	mat4 viewProjectionMatrix;
	vec4 frustumPlanes[6];
} cameraConstants;

layout(set = 1, binding = 0) readonly buffer Vertices {
	Vertex vertices[];
};

layout(set = 1, binding = 1) readonly buffer Meshlets {
	Meshlet meshlets[];
};

layout(set = 1, binding = 2) readonly buffer MeshletData {
	uint meshletData[]; 
};

in taskNV block {
	uint meshletIndices[32];
};

void main() {
	uint ti = gl_LocalInvocationID.x;
	uint mi = meshletIndices[gl_WorkGroupID.x];

	uint vertexCount = uint(meshlets[mi].vertexCount);
	uint triangleCount = uint(meshlets[mi].triangleCount);
	uint indexCount = triangleCount * 3;

	uint dataOffset = meshlets[mi].dataOffset;
	uint indexOffset = dataOffset + vertexCount;

	vec3 meshletColor = vec3(0.0f);
	
	if(visualizationMode == VISUALIZATION_MODE_MESHLETS) {
		meshletColor = murmurHash11Color(mi);
	}
	
	for(uint i = ti; i < vertexCount; i += 32) {
		uint vi = meshletData[dataOffset + i];

		vec3 position = vec3(vertices[vi].posX, vertices[vi].posY, vertices[vi].posZ);
		vec2 texCoord = vec2(vertices[vi].texX, vertices[vi].texY);
		vec3 normal = vec3(int(vertices[vi].normalX), int(vertices[vi].normalY), int(vertices[vi].normalZ)) / 127.0f - 1.0f;

		gl_MeshVerticesNV[i].gl_Position = cameraConstants.viewProjectionMatrix * vec4(position, 1.0f);
	
		if(visualizationMode == VISUALIZATION_MODE_MESHLETS) {
			colors[i] = meshletColor;
		}
	}

	uint indexGroupCount = (indexCount + 3) / 4;

	for(uint i = ti; i < indexGroupCount; i += 32) {
		writePackedPrimitiveIndices4x8NV(i * 4, meshletData[indexOffset + i]);
	}

	if(visualizationMode == VISUALIZATION_MODE_TRIANGLES) {
		for(uint i = ti; i < triangleCount; i += 32) {
			gl_MeshPrimitivesNV[i].gl_PrimitiveID = int(mi * MAX_PRIMITIVES + i);
		}
	}
	
	if(ti == 0) gl_PrimitiveCountNV = uint(meshlets[mi].triangleCount);
}
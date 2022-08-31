#version 460
#extension GL_ARB_separate_shader_objects : enable
#extension GL_GOOGLE_include_directive : require

#extension GL_NV_mesh_shader : require

layout(local_size_x = 32, local_size_y = 1, local_size_z = 1) in;

out taskNV block {
	uint meshletIndices[32];
};

void main() {
	uint ti = gl_LocalInvocationID.x;
	uint mi = gl_GlobalInvocationID.x;
	
	meshletIndices[ti] = mi;
	
	if(ti == 0) gl_TaskCountNV = 32;
}
#version 460
#extension GL_ARB_separate_shader_objects : enable

out gl_PerVertex {
    vec4 gl_Position;
};

layout(location = 0) out vec2 texCoord_FS;

void main() {
    texCoord_FS = vec2((gl_VertexIndex << 1) & 2, gl_VertexIndex & 2);
    gl_Position = vec4(texCoord_FS * 2.0 - 1.0, 0.0, 1.0);
}
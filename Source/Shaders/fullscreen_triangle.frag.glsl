#version 460
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 texCoord_FS;
layout(location = 0) out vec4 outColor0;

layout(set = 0, binding = 0) uniform sampler2D tex;

void main() {
    outColor0 = texture(tex, texCoord_FS);
}
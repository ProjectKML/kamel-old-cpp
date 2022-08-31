#version 460
#extension GL_ARB_separate_shader_objects : enable
#extension GL_GOOGLE_include_directive : require

#include "Util/visualization_mode.h"
#include "Util/hash.h"

layout(constant_id = 0) const uint visualizationMode = VISUALIZATION_MODE_NONE;

layout(location = 0) in vec3 meshletColor;

layout(location = 0) out vec4 diffuseColor;
layout(location = 1) out vec4 normalColor;
layout(location = 2) out vec4 specularColor;

void main() {
	if(visualizationMode == VISUALIZATION_MODE_MESHLETS) {
		diffuseColor = vec4(meshletColor, 1.0f);
	}
	else if(visualizationMode == VISUALIZATION_MODE_TRIANGLES) {
		diffuseColor = vec4(murmurHash11Color(gl_PrimitiveID), 1.0f);
	}
	else {
		diffuseColor = vec4(0.1f, 1.0f, 0.1f, 1.0f); //TODO:
	}
	
	normalColor = vec4(1.0);
	specularColor = vec4(1.0);
}
//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: hash.h
//------------------------------------------------------------

const int MAX_VERTICES = 64;
const int MAX_PRIMITIVES = 124;

struct Vertex {
    float posX, posY, posZ;
    float texX, texY;
    uint8_t normalX, normalY, normalZ, normalW;
};

struct Meshlet {
	float centerX, centerY, centerZ;
	float radius;
	
	uint8_t coneAxisX, coneAxisY, coneAxisZ, coneCutoff;
	
	uint dataOffset;
	uint8_t vertexCount;
	uint8_t triangleCount;
};
//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: hash.h
//------------------------------------------------------------

uint murmurHash11(uint src) {
    const uint M = 0x5bd1e995u;
    uint h = 1190494759u;
    src *= M;
    src ^= src >> 24u;
    src *= M;
    h *= M;
    h ^= src;
    h ^= h >> 13u;
    h *= M;
    h ^= h >> 15u;

    return h;
}

vec3 murmurHash11Color(uint src) {
    uint hash = murmurHash11(src);
    return vec3((hash >> 16u) & 0xFFu, (hash >> 8u) & 0xFFu, hash & 0xFFu) / 256.0f;
}
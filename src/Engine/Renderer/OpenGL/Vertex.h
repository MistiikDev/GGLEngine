#include "Vector3.h"
#include "Vector2.h"

#pragma once

struct Vertex {
    // ORDER MATTERS FOR PASSING ON SHADER
    Vector3 Position;
    Vector3 Color;

    Vector2 TexUV;
    Vector3 Normal;

    bool operator==( const Vertex rhs ) const {
        return Position == rhs.Position && Normal == rhs.Normal && TexUV == rhs.TexUV;
    }
};

// Hashing function for a vertex /
struct VertexHash {
    size_t operator()(const Vertex& v) const {
        size_t p = std::hash<float>{}(v.Position.x) ^ (std::hash<float>{}(v.Position.y) << 1) ^ (std::hash<float>{}(v.Position.z) << 2);
        size_t n = std::hash<float>{}(v.Normal.x) ^ (std::hash<float>{}(v.Normal.y) << 1) ^ (std::hash<float>{}(v.Normal.z) << 2);;
        size_t t = std::hash<float>{}(v.TexUV.x) ^ (std::hash<float>{}(v.TexUV.y) << 1);

        return p ^ n ^ t;
    };
};
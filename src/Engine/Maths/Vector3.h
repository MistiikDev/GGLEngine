#ifndef GGLENGINE_VECTOR3_H
#define GGLENGINE_VECTOR3_H

struct Vector3 {
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {};
    Vector3(float x, float y, float z): x(x), y(y), z(z) {};


    bool operator==(Vector3 rhs) {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
};

#endif
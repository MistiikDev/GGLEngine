#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2 {
    float x, y;

    Vector2() : x(0), y(0) {};
    Vector2( float x, float y ): x(x), y(y) {};
    Vector2( float a ): x(a), y(a) {};

    bool operator== ( const Vector2 rhs ) const {
        return x == rhs.x && y == rhs.y;
    }
};

#endif
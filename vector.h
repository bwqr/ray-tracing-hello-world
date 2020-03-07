
#ifndef RENDER_HELLO_WORLD_VECTOR_H
#define RENDER_HELLO_WORLD_VECTOR_H

#include <cmath>

struct vec2 {
    float x;
    float y;
};

struct vec3 {
    float x;
    float y;
    float z;

    vec3() = default;

    vec3(float _x, float _y, float _z) {
        x = _x;
        y = _y;
        z = _z;
    };

    inline vec3 unit() const {
        return *this / length();
    }

    inline vec3 bisect(const vec3 &other) const {
        return *this * other.length() + other * length();
    }

    inline float cos(const vec3 &other) const {
        return dot(other) / (other.length() * length());
    }

    inline float length() const {
        return std::sqrt(dot(*this));
    }

    inline float dot(const vec3 &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    inline vec3 operator*(const float &t) const {
        return {x * t, y * t, z * t};
    }

    inline vec3 operator/(const float &t) const {
        return {x / t, y / t, z / t};
    }

    inline vec3 operator+(const vec3 &other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    inline vec3 operator-(const vec3 &other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    inline vec3 operator-() const {
        return {-x, -y, -z};
    }

    vec3(const vec2 &other) {
        x = other.x;
        y = other.y;
        z = 0;
    }

    vec3 &operator=(const vec2 &other) {
        x = other.x;
        y = other.y;
        z = 0;

        return *this;
    }
};

#endif //RENDER_HELLO_WORLD_VECTOR_H

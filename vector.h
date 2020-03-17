
#ifndef RENDER_HELLO_WORLD_VECTOR_H
#define RENDER_HELLO_WORLD_VECTOR_H

#include <cmath>
#include <cerrno>

#define REFRACT_ERROR -1
#define NO_ERROR 0
struct vec3;

//Commutative definitions

inline vec3 operator*(const float &f, const vec3 &v);

inline vec3 operator*(const vec3 &v, const float &f);

inline vec3 operator-(const vec3 &v, const float &f);

inline vec3 operator-(const float &f, const vec3 &v);

inline vec3 operator-(const vec3 &v);

inline vec3 operator-(const vec3 &v1, const vec3 &v2);

inline vec3 operator+(const vec3 &v, const float &f);

inline vec3 operator+(const float &f, const vec3 &v);

inline vec3 operator+(const vec3 &v1, const vec3 &v2);

inline vec3 operator/(const float &f, const vec3 &v);

inline vec3 operator/(const vec3 &v, const float &f);

inline vec3 operator/(const vec3 &v1, const vec3 &v2);

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

    inline float distance(const vec3 &other) const {
        return (*this - other).length();
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

    inline vec3 cross(const vec3 &other) const {
        return {y * other.z - z * other.y, -(x * other.z - z * other.x), x * other.y - y * other.x};
    }

    //Other must be normalized
    inline vec3 reflect(const vec3 &other) const {
        return *this - other * 2 * (other.dot(*this));
    }

    //This and Other must be normalized
    inline vec3 refract(const vec3 &normal, const float &n1, const float &n2) {
        float n = n1 / n2;
        float cosi = - dot(normal);
        float sint2 = n * n * (1. - cosi * cosi);

        if (sint2 > 1.0) {
            errno = REFRACT_ERROR;
            return {};
        }

        float cost = std::sqrt(1 - sint2);
        //Clear error
        errno = NO_ERROR;
        return *this * n + (n*cosi - cost) *normal;
    }

    explicit vec3(const vec2 &other) {
        x = other.x;
        y = other.y;
        z = 0;
    }
};

inline vec3 operator*(const vec3 &v, const float &f) {
    return {v.x * f, v.y * f, v.z * f};
}

inline vec3 operator*(const float &f, const vec3 &v) {
    return v * f;
}

inline vec3 operator-(const vec3 &v) {
    return {-v.x, -v.y, -v.z};
}

inline vec3 operator-(const vec3 &v, const float &f) {
    return {v.x - f, v.y - f, v.z - f};
}

inline vec3 operator-(const float &f, const vec3 &v) {
    return v - f;
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

inline vec3 operator+(const vec3 &v, const float &f) {
    return {v.x + f, v.y + f, v.z + f};
}

inline vec3 operator+(const float &f, const vec3 &v) {
    return v + f;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

inline vec3 operator/(const vec3 &v, const float &f) {
    return {v.x / f, v.y / f, v.z / f};
}

inline vec3 operator/(const float &f, const vec3 &v) {
    return v / f;
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
    return {v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};
}


#endif //RENDER_HELLO_WORLD_VECTOR_H

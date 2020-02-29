#ifndef RENDER_HELLO_WORLD_RAY_H
#define RENDER_HELLO_WORLD_RAY_H


#include "vector.h"

class Ray {
public:
    vec3 point;
    vec3 direction;

    Ray() = default;

    Ray(vec3 _point, vec3 _direction) {
        point = _point;
        direction = _direction;
    }

    vec3 move(float t) const {
        return point + direction * t;
    }
};


#endif //RENDER_HELLO_WORLD_RAY_H

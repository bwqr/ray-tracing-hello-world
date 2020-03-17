#ifndef RENDER_HELLO_WORLD_LIGHT_H
#define RENDER_HELLO_WORLD_LIGHT_H

#include "vector.h"

struct Light {
    vec3 position;
    float intensity;

    Light() = default;

    Light(const vec3 &p, const float &i) {
        position = p;
        intensity = i;
    }
};

#endif //RENDER_HELLO_WORLD_LIGHT_H

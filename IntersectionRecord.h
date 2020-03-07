
#ifndef RENDER_HELLO_WORLD_INTERSECTIONRECORD_H
#define RENDER_HELLO_WORLD_INTERSECTIONRECORD_H

#include "vector.h"

struct IntersectionRecord {
    float t;
    vec3 hitPoint;
    vec3 normal;
    vec3 look;
};

#endif //RENDER_HELLO_WORLD_INTERSECTIONRECORD_H

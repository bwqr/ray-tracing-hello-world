
#ifndef RENDER_HELLO_WORLD_INTERSECTIONRECORD_H
#define RENDER_HELLO_WORLD_INTERSECTIONRECORD_H

#include "vector.h"

struct IntersectionRecord {
    float t;
    vec3 hitPoint;
    vec3 normal;
};

#endif //RENDER_HELLO_WORLD_INTERSECTIONRECORD_H

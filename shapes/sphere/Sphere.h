
#ifndef RENDER_HELLO_WORLD_SPHERE_H
#define RENDER_HELLO_WORLD_SPHERE_H


#include "../../surfaces/Surface.h"
#include "../../defs.h"

class Sphere {
public:
    Sphere(vec3 _center, float _radius);

    bool intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax);

protected:
    const vec3 center;
    const float radius;
};


#endif //RENDER_HELLO_WORLD_SPHERE_H

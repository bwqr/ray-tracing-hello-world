
#ifndef RENDER_HELLO_WORLD_SPHERE_H
#define RENDER_HELLO_WORLD_SPHERE_H


#include "../surface/Surface.h"
#include "../defs.h"

class Sphere {
public:
    Sphere(vec3 _center, float _radius);

    bool intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax);

protected:
    vec3 center;
    float radius;
};


#endif //RENDER_HELLO_WORLD_SPHERE_H

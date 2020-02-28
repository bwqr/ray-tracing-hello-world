
#ifndef RENDER_HELLO_WORLD_SPHERE_H
#define RENDER_HELLO_WORLD_SPHERE_H


#include "Surface.h"

class Sphere : public Surface {
public:
    Sphere(vec3 _center, float _radius);

    bool intersect(IntersectionRecord *intersection, const Ray &ray ) override;
    vec3 shade(const IntersectionRecord &intersectionRecord, const vec3 &light, const std::vector<std::unique_ptr<Surface>> &surfaces);

private:
    vec3 center;
    float radius;
};


#endif //RENDER_HELLO_WORLD_SPHERE_H

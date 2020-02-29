
#ifndef RENDER_HELLO_WORLD_SPHERE_H
#define RENDER_HELLO_WORLD_SPHERE_H


#include "Surface.h"

class Sphere : public Surface {
public:
    Sphere(vec3 _center, vec3 _color, float _radius);

    bool intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) override;
    vec3 shade(const IntersectionRecord &record, const vec3 &lightSource, const std::vector<std::unique_ptr<Surface>> &surfaces);

private:
    vec3 center;
    float radius;
    vec3 color;
};


#endif //RENDER_HELLO_WORLD_SPHERE_H


#ifndef RENDER_HELLO_WORLD_SPHERE_H
#define RENDER_HELLO_WORLD_SPHERE_H


#include "Surface.h"
#include "defs.h"

class Sphere : public Surface {
public:
    Sphere(vec3 _center, vec3 _color, float _radius);

    bool intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) override;

    vec3 shade(const IntersectionRecord &record, const Ray &look, const std::vector<vec3> &lightSources,
               const std::vector<std::unique_ptr<Surface>> &surfaces) override;

private:
    vec3 center;
    float radius;
    vec3 color;

    float ks = 0.4;
    float kd = 0.6;
    float ka = AMBIENT_LIGHT;
    float p = 64;
};


#endif //RENDER_HELLO_WORLD_SPHERE_H

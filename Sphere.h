
#ifndef RENDER_HELLO_WORLD_SPHERE_H
#define RENDER_HELLO_WORLD_SPHERE_H


#include "Surface.h"
#include "defs.h"

class Sphere : public Surface {
public:
    Sphere(vec3 _center, vec3 _color, float _radius, float _kd, float _ks, int _p);

    bool intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) override;

    vec3 shade(const IntersectionRecord &record, const std::vector<Light> &lightSources,
               const std::vector<std::unique_ptr<Surface>> &surfaces, const int &depth) override;

    vec3 getColor() override;

protected:
    vec3 center;
    float radius;
    vec3 color;

    float ks;
    float kd;
    float ka = AMBIENT_LIGHT;
    int p;
};


#endif //RENDER_HELLO_WORLD_SPHERE_H



#ifndef RENDER_HELLO_WORLD_DIFFUSEDTRIANGLE_H
#define RENDER_HELLO_WORLD_DIFFUSEDTRIANGLE_H


#include "../../surfaces/DiffusedSurface.h"
#include "Triangle.h"

class DiffusedTriangle : public Triangle, public DiffusedSurface {
public:
    DiffusedTriangle(const std::array<vec3, 3> &_points, const vec3 &_color, float _kd, float _ks, int _p);

    bool intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) override;
};


#endif //RENDER_HELLO_WORLD_DIFFUSEDTRIANGLE_H

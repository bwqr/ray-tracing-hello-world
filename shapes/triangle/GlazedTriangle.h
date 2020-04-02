

#ifndef RENDER_HELLO_WORLD_GLAZEDTRIANGLE_H
#define RENDER_HELLO_WORLD_GLAZEDTRIANGLE_H


#include "../../surfaces/GlazedSurface.h"
#include "Triangle.h"

class GlazedTriangle : public Triangle, public GlazedSurface {
public:
    GlazedTriangle(const std::array<vec3, 3> &_points, const vec3 &_color, float _km);

    bool intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) override;
};


#endif //RENDER_HELLO_WORLD_GLAZEDTRIANGLE_H

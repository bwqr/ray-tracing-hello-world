#ifndef RENDER_HELLO_WORLD_TRIANGLE_H
#define RENDER_HELLO_WORLD_TRIANGLE_H

#include <array>
#include "../../surfaces/Surface.h"
#include "../../defs.h"
#include "../../surfaces/GlazedSurface.h"

class Triangle {
public:
    Triangle(const std::array<vec3, 3> &_points);

    bool intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax);
private:
    const vec3 a, b, c;
};


#endif //RENDER_HELLO_WORLD_TRIANGLE_H

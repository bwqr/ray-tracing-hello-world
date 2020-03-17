//
// Created by fmk on 3/13/20.
//

#ifndef RENDER_HELLO_WORLD_TRIANGLE_H
#define RENDER_HELLO_WORLD_TRIANGLE_H

#include <array>
#include "surface/Surface.h"
#include "defs.h"
#include "surface/GlazedSurface.h"

class Triangle : public GlazedSurface {
public:
    Triangle(const std::array<vec3, 3> &_points, const vec3 &_color, float _kd, float _km);

    bool intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) override;
private:
    vec3 a, b, c;
    vec3 color;
};


#endif //RENDER_HELLO_WORLD_TRIANGLE_H

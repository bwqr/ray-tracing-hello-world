//
// Created by fmk on 3/13/20.
//

#ifndef RENDER_HELLO_WORLD_TRIANGLE_H
#define RENDER_HELLO_WORLD_TRIANGLE_H


#include "Surface.h"
#include "defs.h"

class Triangle: public Surface {
public:
    Triangle(const std::array<vec3, 3> &_points, const vec3 &_color);

    bool intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) override;

    vec3 shade(const IntersectionRecord &record, const std::vector<Light> &lightSources, const std::vector<std::unique_ptr<Surface> > &surfaces) override;

private:
    vec3 a, b, c;
    vec3 color;

    float ka = AMBIENT_LIGHT;
};


#endif //RENDER_HELLO_WORLD_TRIANGLE_H

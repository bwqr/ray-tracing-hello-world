//
// Created by fmk on 3/13/20.
//

#ifndef RENDER_HELLO_WORLD_TRIANGLE_H
#define RENDER_HELLO_WORLD_TRIANGLE_H

#include <array>
#include "Surface.h"
#include "defs.h"

class Triangle : public Surface {
public:
    Triangle(const std::array<vec3, 3> &_points, const vec3 &_color, float _kd, float _km);

    bool intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) override;

    vec3 shade(const IntersectionRecord &record, const std::vector<Light> &lightSources,
               const std::vector<std::unique_ptr<Surface> > &surfaces, const int &depth) override;

    vec3 getColor() override;

private:
    vec3 a, b, c;
    vec3 color;

    float ka = AMBIENT_LIGHT;
    float kd;
    float km;
};


#endif //RENDER_HELLO_WORLD_TRIANGLE_H

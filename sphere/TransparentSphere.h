//
// Created by fmk on 3/16/20.
//

#ifndef RENDER_HELLO_WORLD_TRANSPARENTSPHERE_H
#define RENDER_HELLO_WORLD_TRANSPARENTSPHERE_H


#include "GlazedSphere.h"
#include "../surface/TransparentSurface.h"

class TransparentSphere : protected Sphere, public TransparentSurface {
public:
    TransparentSphere(vec3 _center, float _radius, vec3 _color, float _kd, float _km, float _kt, float _nd);

    bool intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) override;

    vec3 shade(const IntersectionRecord &record, const std::vector<Light> &lightSources,
               const std::vector<std::unique_ptr<Surface> > &surfaces, const int &depth) override;
};


#endif //RENDER_HELLO_WORLD_TRANSPARENTSPHERE_H

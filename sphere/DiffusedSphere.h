//
// Created by fmk on 3/17/20.
//

#ifndef RENDER_HELLO_WORLD_DIFFUSEDSPHERE_H
#define RENDER_HELLO_WORLD_DIFFUSEDSPHERE_H

#include "../surface/DiffusedSurface.h"
#include "Sphere.h"

class DiffusedSphere : public Sphere, public DiffusedSurface {
public:
    DiffusedSphere(const vec3 _center, const float _radius, const vec3 _color, const float _kd,
                   const float _ks, const int _p);

    bool intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) override;
};

#endif //RENDER_HELLO_WORLD_DIFFUSEDSPHERE_H

//
// Created by fmk on 3/16/20.
//

#ifndef RENDER_HELLO_WORLD_TRANSPARENTSPHERE_H
#define RENDER_HELLO_WORLD_TRANSPARENTSPHERE_H


#include "Sphere.h"

class TransparentSphere : public Sphere {
public:
    TransparentSphere(vec3 _center, vec3 _color, float _radius, float _kd, float _km, float _kt, float _nd);

    vec3 shade(const IntersectionRecord &record, const std::vector<Light> &lightSources,
               const std::vector<std::unique_ptr<Surface> > &surfaces, const int &depth) override;

private:
    float km;
    float kt;
    float nd;
};


#endif //RENDER_HELLO_WORLD_TRANSPARENTSPHERE_H

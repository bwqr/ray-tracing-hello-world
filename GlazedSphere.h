//
// Created by fmk on 14.03.2020.
//

#ifndef RENDER_HELLO_WORLD_GLAZEDSPHERE_H
#define RENDER_HELLO_WORLD_GLAZEDSPHERE_H


#include "Sphere.h"

class GlazedSphere : public Sphere {
public:
    GlazedSphere(vec3 _center, vec3 _color, float _radius, float _kd, float _km);

    vec3 shade(const IntersectionRecord &record, const std::vector<Light> &lightSources,
               const std::vector<std::unique_ptr<Surface> > &surfaces, const int &depth) override;
private:

    float km;
};


#endif //RENDER_HELLO_WORLD_GLAZEDSPHERE_H

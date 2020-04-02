#ifndef RENDER_HELLO_WORLD_GLAZEDSPHERE_H
#define RENDER_HELLO_WORLD_GLAZEDSPHERE_H


#include "Sphere.h"
#include "../../surfaces/GlazedSurface.h"

class GlazedSphere : protected Sphere, public GlazedSurface {
public:
    GlazedSphere(vec3 _center, float _radius, vec3 _color, float _km);

    bool intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) override;
};


#endif //RENDER_HELLO_WORLD_GLAZEDSPHERE_H

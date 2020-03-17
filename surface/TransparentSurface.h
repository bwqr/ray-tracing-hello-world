//
// Created by fmk on 3/17/20.
//

#ifndef RENDER_HELLO_WORLD_TRANSPARENTSURFACE_H
#define RENDER_HELLO_WORLD_TRANSPARENTSURFACE_H


#include "GlazedSurface.h"

class TransparentSurface : public GlazedSurface {
public:
    TransparentSurface(const vec3 _color, const float _kd, const float _km, const float _kt, const float _nd);

protected:
    float kt;
    float nd;

    vec3 shadeRefraction(const IntersectionRecord &record, const std::vector<Light> &lightSources,
                    const std::vector<std::unique_ptr<Surface>> &surfaces, const int depth, const bool inOut);
};


#endif //RENDER_HELLO_WORLD_TRANSPARENTSURFACE_H

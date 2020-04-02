#ifndef RENDER_HELLO_WORLD_GLAZEDSURFACE_H
#define RENDER_HELLO_WORLD_GLAZEDSURFACE_H


#include "DiffusedSurface.h"

class GlazedSurface : public DiffusedSurface {
public:
    GlazedSurface(const vec3 _color, const float _km);

    vec3 shade(const IntersectionRecord &record, const std::vector<Light> &lightSources,
               const std::vector<std::unique_ptr<Surface> > &surfaces, const int &depth) override;

protected:
    const float km;

    vec3 shadeReflection(const IntersectionRecord &record, const std::vector<Light> &lightSources,
                         const std::vector<std::unique_ptr<Surface>> &surfaces, const int depth);
};


#endif //RENDER_HELLO_WORLD_GLAZEDSURFACE_H

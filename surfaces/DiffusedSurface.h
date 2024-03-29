#ifndef RENDER_HELLO_WORLD_DIFFUSEDSURFACE_H
#define RENDER_HELLO_WORLD_DIFFUSEDSURFACE_H


#include "Surface.h"
#include "../defs.h"

class DiffusedSurface : public Surface {
public:
    DiffusedSurface(const vec3 _color, const float _kd, const float _ks, const int _p);

    vec3 shade(const IntersectionRecord &record, const std::vector<Light> &lightSources,
               const std::vector<std::unique_ptr<Surface> > &surfaces, const int &depth) override;

protected:
    const vec3 color{};
    const float ka = AMBIENT_LIGHT;
    const float kd;
    const float ks;
    const int p;

    vec3 shadeDiffusion(const IntersectionRecord &record, const std::vector<Light> &lightSources,
                        const std::vector<std::unique_ptr<Surface>> &surfaces);
};


#endif //RENDER_HELLO_WORLD_DIFFUSEDSURFACE_H

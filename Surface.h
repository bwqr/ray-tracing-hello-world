
#ifndef RENDER_HELLO_WORLD_SURFACE_H
#define RENDER_HELLO_WORLD_SURFACE_H

#include <memory>
#include <vector>
#include "IntersectionRecord.h"
#include "Ray.h"
#include "Light.h"

class Surface {
public:
    virtual bool intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) = 0;
    virtual vec3 shade(const IntersectionRecord &record, const std::vector<Light> &lightSources,
                       const std::vector<std::unique_ptr<Surface>> &surfaces, const int &depth) = 0;

    virtual vec3 getColor() = 0;
};


#endif //RENDER_HELLO_WORLD_SURFACE_H

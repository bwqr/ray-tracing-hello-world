
#ifndef RENDER_HELLO_WORLD_SURFACE_H
#define RENDER_HELLO_WORLD_SURFACE_H

#include <memory>
#include <vector>
#include "IntersectionRecord.h"
#include "Ray.h"

class Surface {
public:
    virtual bool intersect(IntersectionRecord *intersection, const Ray &ray) = 0;
    virtual vec3 shade(const IntersectionRecord &intersectionRecord, const vec3 &light, const std::vector<std::unique_ptr<Surface>> &surfaces) = 0;
};


#endif //RENDER_HELLO_WORLD_SURFACE_H

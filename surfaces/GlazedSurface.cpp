#include "GlazedSurface.h"

GlazedSurface::GlazedSurface(const vec3 _color, const float _km) :
        DiffusedSurface(_color, 1, 0, 0), km(_km) {}

vec3 GlazedSurface::shade(const IntersectionRecord &record, const std::vector<Light> &lightSources,
                          const std::vector<std::unique_ptr<Surface> > &surfaces, const int &depth) {
    return shadeReflection(record, lightSources, surfaces, depth);
}

vec3 GlazedSurface::shadeReflection(const IntersectionRecord &record, const std::vector<Light> &lightSources,
                                    const std::vector<std::unique_ptr<Surface>> &surfaces, const int depth) {
    auto diffusedColor = shadeDiffusion(record, lightSources, surfaces);

    if (depth == 0) {
        return diffusedColor;
    }

    Ray reflectionRay = {record.hitPoint, record.look.reflect(record.normal)};

    auto tMax = std::max<float>(reflectionRay.findT(FAR_VIEW), reflectionRay.findT(NEAR_VIEW));
    IntersectionRecord closestRecord = {};
    Surface *closestSurface = findClosestIntersectedSurface(&closestRecord, surfaces, reflectionRay, ERROR_EPSILON,
                                                            tMax);

    vec3 reflectionColor = {0, 0, 0};

    if (closestSurface != nullptr) {
        reflectionColor = reflectionColor + closestSurface->shade(closestRecord, lightSources, surfaces, depth - 1);
    }

    return diffusedColor * (1 - km) + reflectionColor * km;
}

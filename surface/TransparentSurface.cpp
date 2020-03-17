//
// Created by fmk on 3/17/20.
//

#include "TransparentSurface.h"

TransparentSurface::TransparentSurface(const vec3 _color, const float _kd, const float _km, const float _kt,
                                       const float _nd) : GlazedSurface(_color, _kd, _km) {
    kt = _kt;
    nd = _nd;
}

vec3 TransparentSurface::shadeRefraction(const IntersectionRecord &record, const std::vector<Light> &lightSources,
                                         const std::vector<std::unique_ptr<Surface>> &surfaces, const int depth,
                                         const bool inOut) {
    auto diffusedColor = shadeDiffusion(record, lightSources, surfaces);

    if (depth == 0) {
        return diffusedColor;
    }

    Ray refractionRay = {};
    if (inOut) {
        refractionRay = {record.hitPoint, record.look.unit().refract(record.normal, nd, 1)};
    } else {
        refractionRay = {record.hitPoint, record.look.unit().refract(record.normal, 1, nd)};
    }

    //TIR (total internal reflection
    if (errno != REFRACT_ERROR) {
        IntersectionRecord closestRefractionRecord = {};
        float tMax = std::max<float>(refractionRay.findT(NEAR_VIEW), refractionRay.findT(FAR_VIEW));
        Surface *closestRefractionSurface = findClosestIntersectedSurface(&closestRefractionRecord, surfaces,
                                                                          refractionRay, ERROR_EPSILON, tMax);

        if (closestRefractionSurface != nullptr) {
            vec3 refractionColor = closestRefractionSurface->shade(closestRefractionRecord, lightSources, surfaces,
                                                                   depth - 1);

            return refractionColor * kt + diffusedColor;
        }
    }

    auto reflectedColor = shadeReflection(record, lightSources, surfaces, depth);

    return diffusedColor + reflectedColor;
}

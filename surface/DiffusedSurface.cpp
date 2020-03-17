//
// Created by fmk on 3/17/20.
//

#include "DiffusedSurface.h"

DiffusedSurface::DiffusedSurface(const vec3 _color, const float _kd, const float _ks, const int _p) {
    color = _color;
    kd = _kd;
    ks = _ks;
    p = _p;
}

vec3 DiffusedSurface::shadeDiffusion(const IntersectionRecord &record, const std::vector<Light> &lightSources,
                                     const std::vector<std::unique_ptr<Surface>> &surfaces) {
    float intensity = ka;

    for (const auto &light: lightSources) {
        Ray lightRay = {record.hitPoint, light.position - record.hitPoint};

        bool shadowed = false;

        IntersectionRecord tmpRecord = {};

        for (const auto &surface: surfaces) {
            if (surface->intersect(&tmpRecord, lightRay, ERROR_EPSILON, lightRay.findT(light.position.z))) {
                shadowed = true;
                break;
            }
        }

        if (shadowed) {
            continue;
        }

        auto cosTheta = lightRay.direction.cos(record.normal);

        auto bisect = lightRay.direction.bisect(-record.look);

        auto cosAlpha = record.normal.cos(bisect);

        auto distance = light.position.distance(record.hitPoint) / LENGTH_FACTOR;

        auto pointIntensity = light.intensity; //light.intensity / (distance * distance);

        intensity += pointIntensity * (kd * std::max<float>(0, cosTheta) +
                                       ks * std::pow(std::max<float>(0, cosAlpha), p));
    }
    return color * intensity;
}

vec3 DiffusedSurface::shade(const IntersectionRecord &record, const std::vector<Light> &lightSources,
                            const std::vector<std::unique_ptr<Surface> > &surfaces, const int &depth) {
    return shadeDiffusion(record, lightSources, surfaces);
}

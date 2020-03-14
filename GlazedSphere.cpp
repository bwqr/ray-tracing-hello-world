//
// Created by fmk on 14.03.2020.
//

#include "GlazedSphere.h"

GlazedSphere::GlazedSphere(vec3 _center, vec3 _color, float _radius, float _kd, float _km) : Sphere(_center, _color, _radius, _kd, 0, 0){
    km = _km;
}

vec3 GlazedSphere::shade(const IntersectionRecord &record, const std::vector<Light> &lightSources,
                         const std::vector<std::unique_ptr<Surface> > &surfaces, const int &depth) {
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

//        auto distance = light.position.distance(record.hitPoint) / LENGTH_FACTOR;

        auto pointIntensity = light.intensity; //light.intensity / (distance * distance);

        intensity += pointIntensity * kd * std::max<float>(0, cosTheta);
    }

    if(depth == 0) {
        return color * intensity;
    }


    Surface *closestSurface = nullptr;
    IntersectionRecord closestRecord = {};

    auto norm = record.normal.unit();

    Ray reflectionRay = {record.hitPoint, record.look - norm * 2 * (norm.dot( record.look))};

    auto tBest = std::max<float>(reflectionRay.findT(FAR_VIEW), reflectionRay.findT(NEAR_VIEW));

    for (const auto &surface: surfaces) {
        IntersectionRecord tmpRecord = {};

        if (surface->intersect(&tmpRecord, reflectionRay, ERROR_EPSILON, tBest)) {
            tBest = tmpRecord.t;
            closestSurface = surface.get();
            closestRecord = tmpRecord;
        }
    }

    vec3 reflectionColor = {0, 0, 0};

    if (closestSurface != nullptr) {
        reflectionColor = reflectionColor + closestSurface->shade(closestRecord, lightSources, surfaces, depth - 1);

    }

    auto c = color * intensity + reflectionColor * km ;
    return c;
}

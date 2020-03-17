//
// Created by fmk on 3/16/20.
//

#include "TransparentSphere.h"

TransparentSphere::TransparentSphere(vec3 _center, vec3 _color, float _radius, float _kd, float _km, float _kt,
                                     float _nd)
        : Sphere(_center, _color, _radius, _kd, 0, 0) {
    km = _km;
    kt = _kt;
    nd = _nd;
}

vec3 TransparentSphere::shade(const IntersectionRecord &record, const std::vector<Light> &lightSources,
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

        auto distance = light.position.distance(record.hitPoint) / LENGTH_FACTOR;

        auto pointIntensity = light.intensity; //light.intensity / (distance * distance);

        intensity += pointIntensity * kd * std::max<float>(0, cosTheta);
    }

    if (depth == 0) {
        return color * intensity;
    }

    auto norm = record.normal.unit();

    Ray refractionRay = {};
    //Check if normal is looking into the sphere
    {
        auto innerNormal = center - record.hitPoint;
        if (innerNormal.dot(record.normal) > 0) {
            refractionRay = {record.hitPoint, record.look.unit().refract(norm, nd, 1)};
        } else {
            refractionRay = {record.hitPoint, record.look.unit().refract(norm, 1, nd)};
        }
    }

    //Just do refraction
    if (errno != REFRACT_ERROR) {
        IntersectionRecord closestRefractionRecord = {};
        float tMax = std::max<float>(refractionRay.findT(NEAR_VIEW), refractionRay.findT(FAR_VIEW));
        Surface *closestRefractionSurface = findClosestIntersectedSurface(&closestRefractionRecord, surfaces,
                                                                          refractionRay, ERROR_EPSILON, tMax);

        if (closestRefractionSurface != nullptr) {
            vec3 refractionColor = closestRefractionSurface->shade(closestRefractionRecord, lightSources, surfaces,
                                                                   depth - 1);

            return refractionColor * kt + color * intensity;
        }
    }

    //Just do reflection
    Surface *closestReflectionSurface = nullptr;
    IntersectionRecord closestReflectionRecord = {};

    Ray reflectionRay = {record.hitPoint, record.look.reflect(norm)};

    auto tBest = std::max<float>(reflectionRay.findT(FAR_VIEW), reflectionRay.findT(NEAR_VIEW));

    for (const auto &surface: surfaces) {
        IntersectionRecord tmpRecord = {};

        if (surface->intersect(&tmpRecord, reflectionRay, ERROR_EPSILON, tBest)) {
            tBest = tmpRecord.t;
            closestReflectionSurface = surface.get();
            closestReflectionRecord = tmpRecord;
        }
    }

    vec3 reflectionColor = {0, 0, 0};

    if (closestReflectionSurface != nullptr) {
        reflectionColor = reflectionColor +
                          closestReflectionSurface->shade(closestReflectionRecord, lightSources, surfaces, depth - 1);
    }


    auto c = color * intensity + reflectionColor * km;
    return c;
}

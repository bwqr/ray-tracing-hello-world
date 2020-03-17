//
// Created by fmk on 3/16/20.
//

#include "TransparentSphere.h"

TransparentSphere::TransparentSphere(vec3 _center, float _radius, vec3 _color, float _kd, float _km, float _kt,
                                     float _nd)
        : Sphere(_center, _radius), TransparentSurface(_color, _kd, _km, _kt, _nd) {}

bool TransparentSphere::intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) {
    return Sphere::intersect(record, ray, tMin, tMax);
}

vec3 TransparentSphere::shade(const IntersectionRecord &record, const std::vector<Light> &lightSources,
                              const std::vector<std::unique_ptr<Surface> > &surfaces, const int &depth) {
    bool inOut;

    {
        auto radiusNormal = center - record.hitPoint;
        inOut = radiusNormal.dot(record.normal) > ERROR_EPSILON;
    }

    return shadeRefraction(record, lightSources, surfaces, depth, inOut);
}

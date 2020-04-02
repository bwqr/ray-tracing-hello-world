#include "GlazedSphere.h"

GlazedSphere::GlazedSphere(vec3 _center, float _radius, vec3 _color, float _km)
        : Sphere(_center, _radius), GlazedSurface(_color, _km) {}

bool GlazedSphere::intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) {
    return Sphere::intersect(record, ray, tMin, tMax);
}
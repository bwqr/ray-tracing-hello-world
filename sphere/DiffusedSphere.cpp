#include "DiffusedSphere.h"

DiffusedSphere::DiffusedSphere(const vec3 _center, const float _radius, const vec3 _color, const float _kd,
                               const float _ks, const int _p) : Sphere(_center, _radius),
                                                                DiffusedSurface(_color, _kd, _ks, _p) {}

bool DiffusedSphere::intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) {
    return Sphere::intersect(record, ray, tMin, tMax);
}

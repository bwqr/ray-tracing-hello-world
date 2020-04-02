

#include "DiffusedTriangle.h"

DiffusedTriangle::DiffusedTriangle(const std::array<vec3, 3> &_points, const vec3 &_color, float _kd, float _ks, int _p)
        : Triangle(_points), DiffusedSurface(_color, _kd, _ks, _p) {}

bool DiffusedTriangle::intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) {
    return Triangle::intersect(record, ray, tMin, tMax);
}



#include "GlazedTriangle.h"

GlazedTriangle::GlazedTriangle(const std::array<vec3, 3> &_points, const vec3 &_color, float _km) : Triangle(
        _points), GlazedSurface(_color, _km) {}

bool GlazedTriangle::intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) {
    return Triangle::intersect(record, ray, tMin, tMax);
}

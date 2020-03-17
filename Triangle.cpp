#include "Triangle.h"

Triangle::Triangle(const std::array<vec3, 3> &_points, const vec3 &_color, float _kd, float _km)
        : DiffusedSurface(_color, _kd, .4, 64) {
    a = _points[0];
    b = _points[1];
    c = _points[2];
}

bool Triangle::intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) {
    vec3 ab = b - a;
    vec3 ac = c - a;

    vec3 normal = ab.cross(ac);
    //Surface is backfacing
//    if (normal.z > 0) {
//        return false;
//    }

    //Check if ray and plane is parallel
    if (normal.dot(ray.direction) < ERROR_EPSILON) {
        return false;
    }

    // ax + by + cz = d
    float d = normal.dot(a);
    // t = (d - n.rP)/n.rD
    float t = (d - normal.dot(ray.point)) / normal.dot(ray.direction);

    if (t < tMin || t > tMax) {
        return false;
    }

    record->hitPoint = ray.move(t);
    record->t = t;
    record->look = ray.direction;
    record->normal = -normal.unit();

    auto hitA = record->hitPoint - a;
    if (normal.dot(ab.cross(hitA)) < 0) {
        return false;
    }

    // [(C - B)x(Q - B)].n >= 0
    vec3 bc = c - b;
    auto hitB = record->hitPoint - b;
    if (normal.dot(bc.cross(hitB)) < 0) {
        return false;
    }

    vec3 ca = a - c;
    auto hitC = record->hitPoint - c;
    return normal.dot(ca.cross(hitC)) >= 0;
}


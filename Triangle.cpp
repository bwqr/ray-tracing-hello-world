//
// Created by fmk on 3/13/20.
//

#include "Triangle.h"

Triangle::Triangle(const std::array<vec3, 3> &_points, const vec3 &_color) {
    a = _points[0];
    b = _points[1];
    c = _points[2];
    color = _color / COLOR_MAX;
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
    record->normal = normal;

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

vec3 Triangle::shade(const IntersectionRecord &record, const std::vector<Light> &lightSources,
                     const std::vector<std::unique_ptr<Surface> > &surfaces) {
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

        intensity += light.intensity;
    }

    vec3 reflectionColor = {0, 0, 0};

    for (const auto &surface: surfaces) {
        IntersectionRecord tmpRecord = {};
        if(record.look.x > 0 && record.look.x < 2) {
            int k = 0;
        }
        auto norm = record.normal.unit();

        Ray reflectionRay = {record.hitPoint, record.look - norm * 2 * (norm.dot(record.look))};

        if (surface->intersect(&tmpRecord, reflectionRay, ERROR_EPSILON, reflectionRay.findT(FAR_VIEW))) {
            reflectionColor = reflectionColor + surface->shade(tmpRecord, lightSources, surfaces);
        }
    }

    return (color + reflectionColor) * intensity;
}

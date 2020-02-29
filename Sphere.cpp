
#include "Sphere.h"
#include "defs.h"

Sphere::Sphere(vec3 _center, vec3 _color, float _radius) {
    center = _center;
    radius = _radius;
    color = _color;
}

bool Sphere::intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) {
    auto localPoint = ray.point - center;

    auto dirDot = ray.direction.dot(ray.direction);
    auto localDot = ray.direction.dot(localPoint);

    float delta = std::pow(localDot, 2) -
                  dirDot * (localPoint.dot(localPoint) - std::pow(radius, 2));

    if (delta < 0) {
        return false;
    }

    delta = std::sqrt(delta);

    float tPlus = (-localDot + delta) / dirDot;
    float tMinus = (-localDot - delta) / dirDot;

    record->t = ray.move(tMinus).z >= tMin ? tMinus : tPlus;

    record->hitPoint = ray.move(record->t);

    if(record->hitPoint.z > tMax) {
        return false;
    }

    record->normal = record->hitPoint - center;

    return true;
}

vec3 Sphere::shade(const IntersectionRecord &record, const vec3 &lightSource,
                   const std::vector<std::unique_ptr<Surface>> &surfaces) {
    Ray lightRay = {record.hitPoint, lightSource - record.hitPoint};

    bool shadowed = false;

    IntersectionRecord tmpRecord = {};

    for (const auto &surface: surfaces) {
        if (surface.get() != this && surface->intersect(&tmpRecord, lightRay, NEAR_VIEW, FAR_VIEW)) {
            shadowed = true;
            break;
        }
    }

    float cos = lightRay.direction.dot(record.normal) / (record.normal.length() * lightRay.direction.length());

    if (cos > 0.1 && !shadowed) {
        return color * cos;
    } else {
        return color * AMBIENT_LIGHT * (cos + 1);
    }
}
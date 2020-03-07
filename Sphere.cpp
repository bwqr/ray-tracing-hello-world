
#include "Sphere.h"

Sphere::Sphere(vec3 _center, vec3 _color, float _radius) {
    center = _center;
    radius = _radius;
    color = _color / COLOR_MAX;
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

    record->t = tMinus >= tMin ? tMinus : tPlus;

    if (record->t > tMax || record->t < tMin) {
        return false;
    }

    record->hitPoint = ray.move(record->t);

    record->normal = record->hitPoint - center;

    //Check if ray passes through sphere
    float cos = ray.direction.dot(record->normal) / (record->normal.length() * ray.direction.length());
    if (cos > 0) {
        record->normal = -record->normal;
    }

    return true;
}

vec3 Sphere::shade(const IntersectionRecord &record, const Ray &look, const std::vector<vec3> &lightSources,
                   const std::vector<std::unique_ptr<Surface>> &surfaces) {
    auto &lightSource = lightSources[0];
    Ray lightRay = {record.hitPoint, lightSource - record.hitPoint};

    bool shadowed = false;

    IntersectionRecord tmpRecord = {};

    for (const auto &surface: surfaces) {
        if (surface->intersect(&tmpRecord, lightRay, 0.01, lightRay.findT(lightSource.z))) {
            shadowed = true;
            break;
        }
    }

    auto cosTheta = lightRay.direction.cos(record.normal);

    auto bisect = lightRay.direction.bisect(- look.direction);

    auto cosAlpha = record.normal.cos(bisect);

    auto intensity = shadowed ? ka : ka + kd*std::max<float>(0, cosTheta) + ks*std::pow(std::max<float>(0, cosAlpha), p);

    return color * intensity;
}

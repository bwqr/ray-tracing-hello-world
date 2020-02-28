
#include "Sphere.h"

Sphere::Sphere(vec3 _center, float _radius) {
    center = _center;
    radius = _radius;
}

bool Sphere::intersect(IntersectionRecord *intersection, const Ray &ray) {
    auto localPoint = ray.point - center;

    float delta = std::pow(ray.direction.dot(localPoint), 2) -
                  ray.direction.dot(ray.direction) * (localPoint.dot(localPoint) - std::pow(radius, 2));

    if (delta < 0) {
        return false;
    }

    delta = std::sqrt(delta);

    float tPlus = -ray.direction.dot(localPoint) + delta;
    float tMinus = -ray.direction.dot(localPoint) - delta;

    intersection->t = tMinus > 0 ? tMinus : tPlus;

    return intersection->t > 0;
}

vec3 Sphere::shade(const IntersectionRecord &intersectionRecord, const vec3 &light,
                   const std::vector<std::unique_ptr<Surface>> &surfaces) {
    return {.9, .9, .0};
}


#include "Sphere.h"

Sphere::Sphere(vec3 _center, float _radius) : center(_center), radius(_radius) {}

bool Sphere::intersect(IntersectionRecord *record, const Ray &ray, const float &tMin, const float &tMax) {
    //Move ray into sphere space.
    auto localPoint = ray.point - center;

    //Pre calculate some values.
    auto dirDot = ray.direction.dot(ray.direction); // (d.d)
    auto localDot = ray.direction.dot(localPoint); // (d.p)

    float delta = localDot * localDot -
                  dirDot * (localPoint.dot(localPoint) - radius * radius); // ((d.p)^2 - (d.d)((p.p) - R^2))

    //Check if any solutions exist
    if (delta < 0) {
        return false;
    }

    delta = std::sqrt(delta);

    float tPlus = (-localDot + delta) / dirDot;
    float tMinus = (-localDot - delta) / dirDot;

    //Check if tMinus is behind the tMin. If it is, then use tPlus.
    record->t = tMinus >= tMin ? tMinus : tPlus;

    //Check if found t is between given min and max
    if (record->t > tMax || record->t < tMin) {
        return false;
    }

    //Fill the record.
    record->hitPoint = ray.move(record->t);
    record->normal = (record->hitPoint - center).unit();
    record->look = ray.direction;

    //Check if intersection point passes through sphere, If it passes through sphere, then rotate the normal by 180 degree.
    //This is required if we see inside of object.
    float cos = ray.direction.dot(record->normal) / (record->normal.length() * ray.direction.length());
    if (cos > 0) {
        record->normal = -record->normal;
    }

    return true;
}

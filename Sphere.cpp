
#include "Sphere.h"
#include "Light.h"

Sphere::Sphere(vec3 _center, vec3 _color, float _radius, float _kd, float _ks, int _p) {
    center = _center;
    radius = _radius;
    color = _color / COLOR_MAX;
    kd = _kd;
    ks = _ks;
    p = _p;
}

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
    record->normal = record->hitPoint - center;
    record->look = ray.direction;

    //Check if intersection point passes through sphere, If it passes through sphere, then rotate the normal by 180 degree.
    //This is required if we see inside of object.
    float cos = ray.direction.dot(record->normal) / (record->normal.length() * ray.direction.length());
    if (cos > 0) {
        record->normal = -record->normal;
    }

    return true;
}

vec3 Sphere::shade(const IntersectionRecord &record, const std::vector<Light> &lightSources,
                   const std::vector<std::unique_ptr<Surface>> &surfaces, const int &depth) {

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

        auto cosTheta = lightRay.direction.cos(record.normal);

        auto bisect = lightRay.direction.bisect(-record.look);

        auto cosAlpha = record.normal.cos(bisect);

        auto distance = light.position.distance(record.hitPoint) / LENGTH_FACTOR;

        auto pointIntensity = light.intensity; //light.intensity / (distance * distance);

        intensity += pointIntensity * (kd * std::max<float>(0, cosTheta) +
                                       ks * std::pow(std::max<float>(0, cosAlpha), p));
    }
    auto c = color * intensity;
    return c;
}

vec3 Sphere::getColor() {
    return color;
}

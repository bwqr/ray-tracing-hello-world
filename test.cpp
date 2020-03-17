#include <iostream>
#include "vector.h"

int main() {
    vec3 a = {static_cast<float>(1. / std::sqrt(2)), - static_cast<float>(1. / std::sqrt(2)), 0};
    vec3 norm = {0, 1, 0};

    auto ref = a.refract(norm, 1, 1.5);
    bool err = errno == REFRACT_ERROR;
    std::cout << ref.x * ref.x << ref.y * ref.y << ref.z;

    return 0;
}
#ifndef RENDER_HELLO_WORLD_CAMERA_H
#define RENDER_HELLO_WORLD_CAMERA_H

#include "Ray.h"
#include "vector.h"
#include "defs.h"

struct ViewPlane {
    vec3 vertices[4] = {{-IMAGE_WIDTH, -IMAGE_HEIGHT, 100},
                        {-IMAGE_WIDTH, IMAGE_HEIGHT,  100},
                        {IMAGE_WIDTH,  IMAGE_HEIGHT,  100},
                        {IMAGE_WIDTH,  -IMAGE_HEIGHT, 100}};

    vec3 center;

    explicit ViewPlane() {
        center = {0, 0, 0};

        for (const auto vertex : vertices) {
            center = center + vertex;
        }

        center = center / 4.0;
    }
};

class Camera {
public:
    Ray generateRay(const vec2 &pointInViewPanel) {
        vec3 pointInWorldSpace = {pointInViewPanel.x, pointInViewPanel.y, viewPlane.center.z};
        vec3 direction = (pointInWorldSpace - position);
        return {pointInWorldSpace, direction};
    }

private:
    ViewPlane viewPlane;
    vec3 position = {0, 0, 50};
};


#endif //RENDER_HELLO_WORLD_CAMERA_H

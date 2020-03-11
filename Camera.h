#ifndef RENDER_HELLO_WORLD_CAMERA_H
#define RENDER_HELLO_WORLD_CAMERA_H

#include "Ray.h"
#include "vector.h"
#include "defs.h"

class Camera {
public:
    Ray generateRay(const vec2 &pointInViewPanel) {
        static float imageWidth = IMAGE_WIDTH * 2.;
        static float imageHeight = IMAGE_HEIGHT * 2.;

        vec3 pointInWorldSpace = {
                pointInViewPanel.x * imageWidth - IMAGE_WIDTH,
                IMAGE_HEIGHT - pointInViewPanel.y * imageHeight,
                100
        };

        vec3 direction = (pointInWorldSpace - position);

        return {pointInWorldSpace, direction};
    }

private:
    vec3 position = {0, 0, 0};
};


#endif //RENDER_HELLO_WORLD_CAMERA_H

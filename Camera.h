#ifndef RENDER_HELLO_WORLD_CAMERA_H
#define RENDER_HELLO_WORLD_CAMERA_H

#include "Ray.h"
#include "vector.h"
#include "defs.h"

class Camera {
public:
    Ray generateRay(const vec2 &pointInViewPanel) {
        static float xDifference = viewPanel[1].x - viewPanel[0].x;
        static float yDifference = viewPanel[1].y - viewPanel[0].y;
        static float zDifference = viewPanel[1].z - viewPanel[0].z;
        static float xzRatio = zDifference / xDifference;
        static float yzRatio = zDifference / yDifference;
        vec3 pointInWorldSpace = {
                viewPanel[0].x + xDifference * pointInViewPanel.x,
                viewPanel[0].y + yDifference * pointInViewPanel.y,
                viewPanel[0].z + zDifference * pointInViewPanel.y
        };

        vec3 direction = (pointInWorldSpace - position);

        return {pointInWorldSpace, direction};
    }

private:
    //Two points and x axis in 3d space forms a plane.
    std::array<vec3, 3> viewPanel = {{{-IMAGE_WIDTH, -IMAGE_HEIGHT, 100}, {IMAGE_WIDTH, IMAGE_HEIGHT, 100}}};
    vec3 position = {0, 0, -300};
};


#endif //RENDER_HELLO_WORLD_CAMERA_H

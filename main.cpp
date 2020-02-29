#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include "vector.h"
#include "Camera.h"
#include "Surface.h"
#include "Sphere.h"
#include "defs.h"

using namespace std;

int main() {

    ofstream stream("output/output.ppm");
//    auto &stream = cout;

    vector<unique_ptr<Surface>> surfaces;

    surfaces.push_back(unique_ptr<Surface>(new Sphere({20, 40, 280}, {.9, .4, .4}, 10)));
    surfaces.push_back(unique_ptr<Surface>(new Sphere({0, 0, 250}, {.4, .9, .4}, 20)));
    surfaces.push_back(unique_ptr<Surface>(new Sphere({0, -1000, 400}, { .1, .1, .9}, 1000)));

    vec3 light = {-50, 0, 0};

    Camera camera;

    stream << "P3\n" << IMAGE_RES_X << " " << IMAGE_RES_Y << "\n255\n";

    int **image = new int *[IMAGE_RES_X];

    for (int i = 0; i < IMAGE_RES_X; i++) {
        image[i] = new int[IMAGE_RES_Y * 3];
    }

    float pixelPerUnitX = IMAGE_RES_X / IMAGE_WIDTH / 2;
    float pixelPerUnitY = IMAGE_RES_Y / IMAGE_HEIGHT / 2;

    for (int i = 0; i < IMAGE_RES_Y; i++) {
        float normY = IMAGE_HEIGHT - (i + 0.5) / pixelPerUnitY;

        for (int j = 0; j < IMAGE_RES_X; j++) {
            float normX = (j + 0.5) / pixelPerUnitX - IMAGE_WIDTH;
            int k = j * 3;

            image[i][k] = 0;
            image[i][k + 1] = 0;
            image[i][k + 2] = 0;

            auto ray = camera.generateRay({normX, normY});

            IntersectionRecord record = {};

            float tBest = FAR_VIEW;

            for (const auto &surface: surfaces) {
                if (surface->intersect(&record, ray, ray.findT(NEAR_VIEW), tBest)) {
                    tBest = record.t;
                    auto rgb = surface->shade(record, light, surfaces);
                    image[i][k] = 255.99 * rgb.x;
                    image[i][k + 1] = 255.99 * rgb.y;
                    image[i][k + 2] = 255.99 * rgb.z;
                }
            }

            stream << image[i][k] << " " << image[i][k + 1] << " " << image[i][k + 2] << endl;
        }
    }

    return 0;
}

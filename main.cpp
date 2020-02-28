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

    ofstream stream("output.ppm");
//    auto &stream = cout;

    vector<unique_ptr<Surface>> surfaces;

    surfaces.push_back(unique_ptr<Surface>(new Sphere({0, 0, 97.3}, 3)));
    surfaces.push_back(unique_ptr<Surface>(new Sphere({-10, -10, 140}, 3)));

    vec3 light = {50, 50, 50};

    Camera camera(10);

    stream << "P3\n" << IMAGE_RES_X << " " << IMAGE_RES_Y << "\n255\n";

    int **image = new int *[IMAGE_RES_X];

    for (int i = 0; i < IMAGE_RES_X; i++) {
        image[i] = new int[IMAGE_RES_Y * 3];
    }

    float pixelPerUnitX = IMAGE_RES_X / IMAGE_WIDTH / 2;
    float pixelPerUnitY = IMAGE_RES_Y / IMAGE_HEIGHT / 2;

    for (int i = 0; i < IMAGE_RES_X; i++) {
        float normX = IMAGE_WIDTH - (i + 0.5) / pixelPerUnitX;

        for (int j = 0; j < 3 * IMAGE_RES_Y; j += 3) {
            float normY = (j/3 + 0.5) / pixelPerUnitY - IMAGE_HEIGHT;

            image[i][j] = 0;
            image[i][j + 1] = 0;
            image[i][j + 2] = 0;

            auto ray = camera.generateRay({normX, normY});

            IntersectionRecord record = {};

            float tBest = MAXFLOAT;

            for (const auto &surface: surfaces) {
                if (surface->intersect(&record, ray)) {
                    if (tBest > record.t) {
                        tBest = record.t;
                        auto rgb = surface->shade(record, light, surfaces);
                        image[i][j] = 255.99 * rgb.x;
                        image[i][j + 1] = 255.99 * rgb.y;
                        image[i][j + 2] = 255.99 * rgb.z;
                    }
                }
            }

            stream << image[i][j] << " " << image[i][j + 1] << " " << image[i][j + 2] << endl;
        }
    }

    return 0;
}

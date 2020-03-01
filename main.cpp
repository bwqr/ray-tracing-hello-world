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

    int size = IMAGE_RES_Y * IMAGE_RES_X * 11 + 200;

    string output;
    output.reserve(size);

    ofstream stream("output/output.ppm", ios::binary | ios::trunc);

    vector<unique_ptr<Surface>> surfaces;

    surfaces.push_back(unique_ptr<Surface>(new Sphere({50, 50, 250}, {255, 0, 10}, 20)));
    surfaces.push_back(unique_ptr<Surface>(new Sphere({75, 100, 250}, {10, 255, 10}, 40)));
    surfaces.push_back(unique_ptr<Surface>(new Sphere({0, -1100, 500}, {0, 0, 255}, 1050)));

    vec3 light = {0, 500, 0};

    Camera camera;

    output += "P3\n" + to_string(IMAGE_RES_X) + " " + to_string(IMAGE_RES_Y) + "\n" +
              to_string(static_cast<int>(COLOR_MAX)) + "\n";

    for (int i = 0; i < IMAGE_RES_Y; i++) {
        float normY = (i + 0.5) / IMAGE_RES_Y;

        for (int j = 0; j < IMAGE_RES_X; j++) {

            float normX = (j + 0.5) / IMAGE_RES_X;

            int color[3] = {0, 0, 0};

            auto ray = camera.generateRay({normX, normY});

            IntersectionRecord record = {};

            float tBest = ray.findT(FAR_VIEW);

            for (const auto &surface: surfaces) {
                if (surface->intersect(&record, ray, ray.findT(NEAR_VIEW), tBest)) {
                    tBest = record.t;
                    auto rgb = surface->shade(record, light, surfaces);
                    color[0] = COLOR_MAX * rgb.x;
                    color[1] = COLOR_MAX * rgb.y;
                    color[2] = COLOR_MAX * rgb.z;
                }
            }

            output += to_string(color[0]) + " " + to_string(color[1]) + " " + to_string(color[2]) + "\n";
        }
    }

    stream.write(output.c_str(), output.size());

    stream.close();

    return 0;
}

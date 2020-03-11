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

int main(int argc, char **argv) {

    if(argc < 2) {
        cout << "input file is not given" << endl;

        return -1;
    }

    ofstream stream("output.ppm", ios::binary | ios::trunc);

    if(!stream.is_open()) {
        cout << "output file could not be open" << endl;

        return -1;
    }

    int size = IMAGE_RES_Y * IMAGE_RES_X * 12 + 200;

    string output;
    output.reserve(size);

    vec3 light = {500, 500, 500};
    Camera camera;
    vector<unique_ptr<Surface>> surfaces;

    {
        int num;
        float x, y, z, r, g, b, radius;
        string line;
        ifstream istream(argv[1]);

        if(!istream.is_open()) {
            cout << "input file could not be open" << endl;

            return -1;
        }

        istream >> num;
        surfaces.reserve(num);
        while(!istream.eof()) {
            istream >> x >> y >> z >> r >> g >> b >> radius;
            surfaces.emplace_back(new Sphere({x, y, z}, {r, g, b}, radius));
        }
    }

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
            float tMin = ray.findT(NEAR_VIEW);
            Surface *closestSurface = nullptr;
            IntersectionRecord closestRecord = {};
            for (const auto &surface: surfaces) {
                if (surface->intersect(&record, ray, tMin, tBest)) {
                    tBest = record.t;
                    closestRecord = record;
                    closestSurface = surface.get();
                }
            }

            if(closestSurface != nullptr) {
                auto rgb = closestSurface->shade(closestRecord, {light}, surfaces) * COLOR_MAX;
                color[0] = rgb.x;
                color[1] = rgb.y;
                color[2] = rgb.z;
            }

            output += to_string(color[0]) + " " + to_string(color[1]) + " " + to_string(color[2]) + "\n";
        }
    }

    stream.write(output.c_str(), output.size());

    stream.close();

    return 0;
}

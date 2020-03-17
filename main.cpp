#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include <array>
#include "vector.h"
#include "Camera.h"
#include "Surface.h"
#include "Sphere.h"
#include "defs.h"
#include "Triangle.h"
#include "GlazedSphere.h"
#include "TransparentSphere.h"

using namespace std;

int read_file(char *path, std::vector<unique_ptr<Surface>> *surfaces, std::vector<Light> *lights);

int main(int argc, char **argv) {

    if (argc < 3) {
        cout << "input and output file is not given" << endl;

        return -1;
    }

    ofstream stream(argv[2], ios::binary | ios::trunc);

    if (!stream.is_open()) {
        cout << "output file could not be open" << endl;

        return -1;
    }

    int size = IMAGE_RES_Y * IMAGE_RES_X * 12 + 200;

    string output;
    output.reserve(size);

    Camera camera;
    vector<unique_ptr<Surface>> surfaces;
    vector<Light> lights;

    if (read_file(argv[1], &surfaces, &lights) != 0) {
        cout << "input file could not be open" << endl;

        return -1;
    }

    output += "P3\n" + to_string(IMAGE_RES_X) + " " + to_string(IMAGE_RES_Y) + "\n" +
              to_string(static_cast<int>(COLOR_MAX)) + "\n";

    for (int i = IMAGE_RES_Y - 1; i >= 0; i--) {
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

            if (closestSurface != nullptr) {
                auto rgb = closestSurface->shade(closestRecord, lights, surfaces, 3) * COLOR_MAX;
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

int read_file(char *path, std::vector<unique_ptr<Surface>> *surfaces, std::vector<Light> *lights) {
    string type;
    int p, numObject;
    float x, y, z, r, g, b, ks, kd, radius, intensity, km, kt, nd;
    string line;
    ifstream istream(path);

    if (!istream.is_open()) {
        return -1;
    }

    istream >> numObject;

    while (!istream.eof()) {
        istream >> type;
        if (type == "sphere") {
            istream >> x >> y >> z >> r >> g >> b >> radius >> kd >> ks >> p;
            surfaces->emplace_back(new Sphere({x, y, z}, {r, g, b}, radius, kd, ks, p));
        } else if (type == "triangle") {
            std::array<vec3, 3> points = {};

            for (size_t j = 0; j < 3; j++) {
                istream >> x >> y >> z;
                points[j] = {x, y, z};
            }

            istream >> r >> g >> b >> kd >> km;

            surfaces->emplace_back(new Triangle(points, {r, g, b}, kd, km));
        } else if (type == "light") {
            istream >> x >> y >> z >> intensity;
            lights->emplace_back(Light({x, y, z}, intensity));
        } else if (type == "glazedsphere") {
            istream >> x >> y >> z >> r >> g >> b >> radius >> kd >> km;
            surfaces->emplace_back(new GlazedSphere({x, y, z}, {r, g, b}, radius, kd, km));
        } else if (type == "transsphere") {
            istream >> x >> y >> z >> r >> g >> b >> radius >> kd >> km >> kt >> nd;
            surfaces->emplace_back(new TransparentSphere({x, y, z}, {r, g, b}, radius, kd, km, kt, nd));
        } else {
            istream.ignore(INT32_MAX, '\n');
        }
    }

    return 0;
}
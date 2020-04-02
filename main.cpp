#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include "vector.h"
#include "Camera.h"
#include "surfaces/Surface.h"
#include "shapes/sphere/Sphere.h"
#include "shapes/triangle/Triangle.h"
#include "shapes/sphere/GlazedSphere.h"
#include "shapes/sphere/TransparentSphere.h"
#include "shapes/sphere/DiffusedSphere.h"
#include "shapes/triangle/GlazedTriangle.h"
#include "shapes/triangle/DiffusedTriangle.h"

using namespace std;

int read_file(char *path, std::vector<unique_ptr<Surface>> *surfaces, std::vector<Light> *lights);

int main(int argc, char **argv) {

    if (argc < 3) {
        cout << "input and output file is not given" << endl;

        return -1;
    }

    ofstream stream(argv[2], ios::binary | ios::trunc);

    if (!stream.is_open()) {
        cout << "output file could not be opened" << endl;

        return -1;
    }

    int size = IMAGE_RES_Y * IMAGE_RES_X * 12 + 200;

    string output;
    output.reserve(size);

    Camera camera;
    vector<unique_ptr<Surface>> surfaces;
    vector<Light> lights;

    if (read_file(argv[1], &surfaces, &lights) != 0) {
        cout << "input file could not be opened" << endl;

        return -1;
    }

    output += "P3\n" + to_string(IMAGE_RES_X) + " " + to_string(IMAGE_RES_Y) + "\n" +
              to_string(static_cast<int>(COLOR_MAX)) + "\n";

    auto *image = new int16_t[IMAGE_RES_Y * IMAGE_RES_Y * 3];

#pragma omp parallel for default(none) shared(camera, surfaces, image, lights)
    for (int i = IMAGE_RES_Y - 1; i >= 0; i--) {
        float normY = (i + 0.5) / IMAGE_RES_Y;

        for (int j = 0; j < IMAGE_RES_X; j++) {

            float normX = (j + 0.5) / IMAGE_RES_X;

            int index = i * IMAGE_RES_X * 3 + j * 3;

            image[index] = 0;
            image[index + 1] = 0;
            image[index + 2] = 0;

            auto ray = camera.generateRay({normX, normY});

            IntersectionRecord closestRecord = {};
            Surface *closestSurface = Surface::findClosestIntersectedSurface(&closestRecord, surfaces, ray,
                                                                             ray.findT(NEAR_VIEW),
                                                                             ray.findT(FAR_VIEW));
            if (closestSurface != nullptr) {
                auto rgb = closestSurface->shade(closestRecord, lights, surfaces, 3) * COLOR_MAX;
                image[index] = rgb.x;
                image[index + 1] = rgb.y;
                image[index + 2] = rgb.z;

                if(rgb.x > COLOR_MAX || rgb.y > COLOR_MAX || rgb.z > COLOR_MAX) {
                    throw std::runtime_error("overflow");
                }
            }
        }
    }

    for (int i = IMAGE_RES_Y - 1; i >= 0; i--) {
        for (int j = 0; j < IMAGE_RES_X; ++j) {
            int index = i * IMAGE_RES_X * 3 + j * 3;

            output += to_string(image[index]) + " " +
                      to_string(image[index + 1]) + " " +
                      to_string(image[index + 2]) + "\n";
        }
    }

    stream.write(output.c_str(), output.size());

    stream.close();

    delete[] image;
    return 0;
}

int read_file(char *path, std::vector<unique_ptr<Surface>> *surfaces, std::vector<Light> *lights) {
    string type;
    int p;
    float x, y, z, r, g, b, ks, kd, radius, intensity, km, kt, nd;
    string line;
    ifstream istream(path);

    if (!istream.is_open()) {
        return -1;
    }


    while (!istream.eof()) {
        istream >> type;
        if (type == "sphere") {
            istream >> x >> y >> z >> r >> g >> b >> radius >> kd >> ks >> p;
            vec3 color = {r, g, b};

            surfaces->emplace_back(new DiffusedSphere({x, y, z}, radius, color / COLOR_MAX, kd, ks, p));
        } else if (type == "triangle") {
            std::array<vec3, 3> points = {};

            for (size_t j = 0; j < 3; j++) {
                istream >> x >> y >> z;
                points[j] = {x, y, z};
            }

            istream >> r >> g >> b >> kd >> ks >> p;
            vec3 color = {r, g, b};

            surfaces->emplace_back(new DiffusedTriangle(points, color / COLOR_MAX, kd, ks, p));
        } else if (type == "light") {
            istream >> x >> y >> z >> intensity;
            lights->emplace_back(Light({x, y, z}, intensity));
        } else if (type == "glazedsphere") {
            istream >> x >> y >> z >> r >> g >> b >> radius >> km;
            vec3 color = {r, g, b};

            surfaces->emplace_back(new GlazedSphere({x, y, z}, radius, color / COLOR_MAX, km));
        } else if (type == "transsphere") {
            istream >> x >> y >> z >> r >> g >> b >> radius >> km >> kt >> nd;
            vec3 color = {r, g, b};
            surfaces->emplace_back(new TransparentSphere({x, y, z}, radius, color / COLOR_MAX, km, kt, nd));
        } else if (type == "gtriangle") {
            std::array<vec3, 3> points = {};

            for (size_t j = 0; j < 3; j++) {
                istream >> x >> y >> z;
                points[j] = {x, y, z};
            }

            istream >> r >> g >> b >> km;
            vec3 color = {r, g, b};

            surfaces->emplace_back(new GlazedTriangle(points, color / COLOR_MAX, km));
        } else if (type == "end") {
            break;
        } else {
            istream.ignore(INT32_MAX, '\n');
        }
    }

    return 0;
}
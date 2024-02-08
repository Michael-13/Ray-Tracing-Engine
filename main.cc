#include "camera.h"
#include "color.h"
#include "hittableList.h"
#include "material.h"
#include "cylinder.h"
#include "plane.h"
#include "sphere.h"
#include <chrono>


using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
int main() {
    hittableList shapes;

    auto meta = std::make_shared<metal>(color(0.5, 0.5, 0.5), 0.0);
    auto solid = std::make_shared<lambertian>(color(0.8,0.2,0.2));
    auto ground = std::make_shared<lambertian>(color(0.4, 0.4, 0.4));
    shapes.add(std::make_shared<sphere>(point3(2.4,0,0), 1, solid));
    shapes.add(std::make_shared<cylinder>(-1, 1, meta));
    shapes.add(std::make_shared<sphere>(point3(0,-110,0),109, ground));
    
    camera cam;

    cam.setAspectRatio(16.0/9.0);
    cam.setImgWidth(400);
    cam.setSamples(500);
    cam.setfov(50.0);
    cam.setCameraPos(point3(6,1,-4), point3(0,0,0), vec3(0,1,0));


    auto t1 = high_resolution_clock::now();
    cam.render(shapes);
    auto t2 = high_resolution_clock::now();

    auto ms_int = duration_cast<seconds>(t2 - t1);
    std::cerr << ms_int.count() << "s\n";
}
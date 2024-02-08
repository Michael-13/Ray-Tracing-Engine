#include "ray.h"

ray::ray() {}

ray::ray(const point3& orgin, const vec3& direction) : orig(orgin), dir(direction) {}

point3 ray::orgin() const {
    return orig;
}

vec3 ray::direction() const {
    return dir;
}

point3 ray::at(double t) const {
    return orig + (dir * t);
}
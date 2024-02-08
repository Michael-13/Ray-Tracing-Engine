#include "hittable.h"

void hitRecord::setFaceNormal(const ray &r, const vec3 &outwardNorm) {
    frontFace = dot(r.direction(), outwardNorm) < 0;
    normal = frontFace ? outwardNorm : -outwardNorm;
}

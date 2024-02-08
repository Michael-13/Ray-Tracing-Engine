#ifndef HITTABLE_H
#define HITTABLE_H
#include "vec3.h"
#include "ray.h"
#include "interval.h"
#include <memory>

class material;

class hitRecord {
    public:
        point3 p; // this is the point of intersection
        vec3 normal;
        std::shared_ptr<material> mat;
        double t; // this is the intersection t value
        bool frontFace;

        void setFaceNormal(const ray &r, const vec3 &outwardNorm);
};

class hittable {
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray &r, interval tInt, hitRecord &hitRec) const = 0;
};

#endif
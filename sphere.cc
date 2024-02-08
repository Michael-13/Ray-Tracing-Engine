#include "sphere.h"

sphere::sphere(point3 cen, double rad, std::shared_ptr<material> material) 
       : centre{cen}, radius{rad}, mat{material} {}

bool sphere::hit(const ray &r, interval tInt, hitRecord &hitRec) const {
    vec3 deltaOC = r.orgin() - centre;
    double a = r.direction().length_squared();
    double b = dot(deltaOC, r.direction());
    double c = deltaOC.length_squared() - (radius * radius);
    double discriminant = b*b - a*c;
    
    if (discriminant < 0) return false;

    double sqrtd = sqrt(discriminant);
    double root = (-b - sqrtd) / a;
    // checks if the root is within range
    if (!tInt.surrounds(root)) {
        root = (-b + sqrtd) / a;
        if (!tInt.surrounds(root)) return false;
    }
    // if it is within the hit range update hit record
    hitRec.t = root;
    hitRec.p = r.at(root);
    vec3 outwardNorm = (hitRec.p - centre) / radius;
    hitRec.setFaceNormal(r, outwardNorm);
    hitRec.mat = mat;
    return true;
}


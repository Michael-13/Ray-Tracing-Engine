#include "plane.h"

plane::plane(vec3 n, point3 pnt, std::shared_ptr<material> m) : norm{n}, pOp{pnt}, mat{m} {}

bool plane::hit(const ray &r, interval tInt, hitRecord &hitRec) const {
    vec3 deltaPO = pOp - r.orgin();
    double num = dot(norm, deltaPO);
    double denom = dot(norm, r.direction());

    if (denom == 0.0) return false;

    double root = num / denom;
    // check if ray intersects with the plane
    if (root < 0.0) return false;

    hitRec.t = root;
    hitRec.p = r.at(root);
    hitRec.setFaceNormal(r, -norm);
    hitRec.mat = mat;
    return true;
}


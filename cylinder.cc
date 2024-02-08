#include "cylinder.h"

cylinder::cylinder(double min, double max, std::shared_ptr<material> m) 
                    : zInt{min,max}, mat{m} {}

bool cylinder::hit(const ray &r, interval tInt, hitRecord &hitRec) const {
    double a = pow(r.direction().x(), 2) + pow(r.direction().y(), 2);
    double b = (2 * r.orgin().x() * r.direction().x()) 
             + (2 * r.orgin().y() * r.direction().y());
    double c = pow(r.orgin().x(), 2) + pow(r.orgin().y(), 2) - 1;
    double discriminant = (b*b) - (4*a*c);

    if (discriminant < 0) return false;

    double sqrtd = sqrt(discriminant);
    // Find the root
    double t1 = (-b - sqrtd) / (2*a);
    double t2 = (-b + sqrtd) / (2*a);


    double z1 = zInt.surrounds(r.at(t1).z()) ? r.at(t1).z() : infinity;
    double z2 = zInt.surrounds(r.at(t2).z()) ? r.at(t2).z() : infinity;
    double root = 0.0;

    if ((z1 == infinity) && (z2 == infinity)) return false;
    else if (z1 == infinity) root = t2;
    else if (z2 == infinity) root = t1;
    else {
        if (t1 > 0 && t2 > 0) root = (t1 < t2) ? t1 : t2;
        else if (t1 > 0) root = t1;
        else if (t2 > 0) root = t2;
        else return false;
    }
    if (!tInt.surrounds(root))  return false;

    // if it is within the hit range update hit record
    hitRec.t = root;
    hitRec.p = r.at(root);
    double normX = hitRec.p.x() / (sqrt(pow(hitRec.p.x(),2) + pow(hitRec.p.y(), 2)));
    double normY = hitRec.p.y() / (sqrt(pow(hitRec.p.x(),2) + pow(hitRec.p.y(), 2)));
    vec3 outwardNorm = vec3(normX, normY, 0);
    hitRec.setFaceNormal(r, outwardNorm);
    hitRec.mat = mat;
    return true;
}
#ifndef PLANE_H
#define PLANE_H

#include "hittable.h"

class plane : public hittable {
    private:
        vec3 norm;
        point3 pOp;
        std::shared_ptr<material> mat;
    public:
        plane(vec3 n, point3 pnt, std::shared_ptr<material> m);

        bool hit(const ray &r, interval tInt, hitRecord &hitRec) const override;
};

#endif
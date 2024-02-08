#ifndef CYLINDER_H
#define CYLINDER_H
#include "hittable.h"

class cylinder : public hittable {
    private:
        point3 centre;
        interval zInt;
        std::shared_ptr<material> mat;
    public:
        cylinder(double min, double max, std::shared_ptr<material> m);

        bool hit(const ray &r, interval tInt, hitRecord &hitRec) const override;

};

#endif

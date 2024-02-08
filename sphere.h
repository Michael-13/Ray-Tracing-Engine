#ifndef HITSPHERE_H
#define HITSPHERE_H
#include "hittable.h"

class sphere : public hittable {
    private:
        point3 centre;
        double radius;
        std::shared_ptr<material> mat;
    public:
        sphere(point3 cen, double rad, std::shared_ptr<material> material);

        bool hit(const ray &r, interval tInt, hitRecord &hitRec) const override;  

};

#endif
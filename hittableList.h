#ifndef HITTABLELIST_H
#define HITTABLELIST_H
#include <vector>
#include <memory>
#include "hittable.h"

class hittableList : public hittable {
    private:
        std::vector<std::shared_ptr<hittable>> objects;
    public:
        hittableList();
        hittableList(std::vector<std::shared_ptr<hittable>> lst);
        hittableList(std::shared_ptr<hittable> obj);

        void clear();
        void add(std::shared_ptr<hittable> obj);

        bool hit(const ray &r, interval tInt, hitRecord &hitRec) const override;
};

#endif
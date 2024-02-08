#include "hittableList.h"

hittableList::hittableList() {}

hittableList::hittableList(std::vector<std::shared_ptr<hittable>> lst) : objects{lst} {}

hittableList::hittableList(std::shared_ptr<hittable> obj) {add(obj);}

void hittableList::clear() {
    objects.clear();
}

void hittableList::add(std::shared_ptr<hittable> obj) {
    objects.emplace_back(obj);
}

bool hittableList::hit(const ray &r, interval tInt, hitRecord &hitRec) const {
    hitRecord tempRec;
    bool hitAnything = false;
    double closestSoFar = tInt.getMax();

    for (const auto & obj: objects) {
        if (obj->hit(r, interval(tInt.getMin(), closestSoFar), tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            hitRec = tempRec;
        }
    }
    return hitAnything;
}

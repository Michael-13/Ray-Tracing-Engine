#ifndef RAY_H
#define RAY_H
#include "vec3.h"
class ray {
    public:
        ray();
        ray(const point3& orgin, const vec3& direction);

        point3 orgin() const;
        vec3 direction() const;

        point3 at(double t) const;
    
    private:
        point3 orig;
        vec3 dir;
};
#endif
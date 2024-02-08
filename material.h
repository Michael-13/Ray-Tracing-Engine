#ifndef MATERIAL_H
#define MATERIAL_H

#include "util.h"
#include "ray.h"
#include "color.h"
#include "hittable.h"

class material {
    public:
        virtual ~material() = default;

        virtual bool scatter(const ray &rin, const hitRecord &rec, 
                             color &attenuation, ray &scattered) const = 0;
};

class lambertian : public material {
    private:
        color albedo;
    public:
        lambertian(const color &a);

        bool scatter(const ray &rin, const hitRecord &rec,
                            color &attenuation, ray &scattered) const override;
         
};

class metal : public material {
    private:
        color albedo;
        double fuzz;
    public:
        metal(const color &a, double f);

        bool scatter(const ray &rin, const hitRecord &rec,
                            color &attenuation, ray &scattered) const override;
         
};

class dielectric : public material {
    private:
        double ir; // Index of Refrection
        static double reflectance(double cosine, double refIdx);
    public:
        dielectric(double indexOfRefraction);

        bool scatter(const ray &rin, const hitRecord &rec,
                            color &attenuation, ray &scattered) const override;

};

#endif

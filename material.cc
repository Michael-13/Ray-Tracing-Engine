#include "material.h"

lambertian::lambertian(const color &a) : albedo{a} {}

bool lambertian::scatter(const ray &rin, const hitRecord &rec,
                            color &attenuation, ray &scattered) const {

    vec3 scatterDir = rec.normal + randomUnitVector();

    // Cathc degenerate scatter direction
    if (scatterDir.nearZero()) {
        scatterDir = rec.normal;
    }

    scattered = ray(rec.p, scatterDir);
    attenuation = albedo;
    return true;
}

metal::metal(const color &a, double f) : albedo{a}, fuzz{f < 1 ? f : 1} {}

bool metal::scatter(const ray &rin, const hitRecord &rec,
                            color &attenuation, ray &scattered) const {
    vec3 reflected = reflect(unit_vector(rin.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz*randomUnitVector());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

dielectric::dielectric(double indexOfRefraction) : ir{indexOfRefraction} {}

double dielectric::reflectance(double cosine, double refIdx) {
    // Use Schlick's approximation for reflectance
    double r0 = (1-refIdx)/(1+refIdx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1-cosine),5);
}

bool dielectric::scatter(const ray &rin, const hitRecord &rec,
                            color &attenuation, ray &scattered) const {
    attenuation = color(1.0,1.0,1.0);
    double refractionRatio = rec.frontFace ? (1.0/ir) : ir;

    vec3 unitDir = unit_vector(rin.direction());
    double cosTheta = fmin(dot(-unitDir, rec.normal), 1.0);
    double sinTheta = sqrt(1 - cosTheta*cosTheta);

    bool cannotRefract = refractionRatio * sinTheta > 1.0;
    vec3 direction;

    if (cannotRefract || reflectance(cosTheta, refractionRatio) > random_double()) {
        direction = reflect(unitDir, rec.normal);
    } else {
        direction = refract(unitDir, rec.normal, refractionRatio);
    }

    scattered = ray(rec.p, direction);
    return true;
}
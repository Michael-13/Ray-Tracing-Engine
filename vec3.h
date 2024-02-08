#ifndef VEC3_H
#define VEC3_H

#include "util.h"
#include <cmath>
#include <iostream>
using std::sqrt;

class vec3 {
    public:
        double e[3];

        // constructors
        vec3();
        vec3(double e0, double e1, double e2);

        // fetchers
        double x() const;
        double y() const;
        double z() const;

        // operators
        vec3 operator-() const;
        double operator[](int i) const;
        double& operator[](int i);
        vec3& operator+=(const vec3 &v);
        vec3& operator*=(double t);
        vec3& operator/=(double t);

        double length_squared() const;
        double length() const;
        bool nearZero() const;
        static vec3 random();
        static vec3 random(double min, double max);
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;


// Vector Utility Functions

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

inline vec3 randomInUnitDisk() {
    while (true) {
        vec3 p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() < 1) {
            return p;
        }
    }
}

inline vec3 randomInUnitSphere() {
    while (true) {
        vec3 p = vec3::random(-1,1);
        if (p.length_squared() < 1) return p;
    }
}

inline vec3 randomUnitVector() {
    return unit_vector(randomInUnitSphere());
}

inline vec3 randomOnHemisphere(const vec3& norm) {
    vec3 onUnitSphere = randomUnitVector();
    if (dot(onUnitSphere, norm) > 0.0) {
        // in the same hemisphere
        return onUnitSphere;
    } else {
        return -onUnitSphere;
    }
}

inline vec3 reflect(const vec3 &v, const vec3 &n) {
    return v - 2*dot(v,n)*n;
}

inline vec3 refract(const vec3 &uv, const vec3 &n, double etaDiv) {
    double cosTheta = fmin(dot(-uv, n), 1.0);
    vec3 Rperp = etaDiv * (uv + cosTheta*n);
    vec3 Rpara = -sqrt(fabs(1.0 - Rperp.length_squared())) * n;
    return Rperp + Rpara;
}

#endif

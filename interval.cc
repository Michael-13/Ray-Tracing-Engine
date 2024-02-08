#include "interval.h"

interval::interval() {}

interval::interval(double min, double max) : min{min}, max{max} {}

double interval::getMin() const {
    return min;
}

double interval::getMax() const {
    return max;
}

bool interval::contains(double x) const {
    if (x >= min && x <= max) {
        return true;
    } else {
        return false;
    }
}

bool interval::surrounds(double x) const {
    if (x > min && x < max) {
        return true; 
    } else {
        return false;
    }
}

double interval::clamp(double x) const {
    if (min > x) return min;
    if (max < x) return max;
    return x;
}

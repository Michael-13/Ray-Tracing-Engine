#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
    private:
        double min, max;
    public:
        interval();
        interval(double min, double max);

        double getMin() const;
        double getMax() const;
        bool contains(double x) const;
        bool surrounds(double x) const;
        double clamp(double x) const;
};

#endif

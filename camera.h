#ifndef CAMERA_H
#define CAMERA_H

#include "util.h"
#include "color.h"
#include "vec3.h"
#include "hittable.h"
#include "ray.h"
#include "material.h"

class camera {
    private:
        double aspectRatio = 1.0;
        int imgWidth = 100;
        int samplesPerPixel = 10;
        int recurseLim = 50;
        
        double fov = 90; // Vertical view angle
        point3 lookfrom = point3(0,0,-1); // Point camera is looking from
        point3 lookat = point3(0,0,0); // Point camera is looking at
        vec3 vup = vec3(0,1,0); // Camera-relative "up" direction

        double defocusAngle = 0; // Variation angle of rays through each pixel
        double focusDist = 10; // Distance from camera lookfrom point to plane perfect focus
        int imgHeight;
        point3 cameraCentre;
        point3 pixel00Location;
        vec3 pixelDeltaU;
        vec3 pixelDeltaV;
        vec3 u, v, w; // Camera frame basis vectors
        vec3 defocusDiskU; // Defocus disk horizontal radius
        vec3 defocusDiskV; // Defocus disk vertical radius

        void initialize();
        color rayColor(const ray &r, const hittable &obj, int count);
        point3 defocusDiskSample() const;
        ray getRay(int u,int v);
        vec3 pixelSampleSquare() const;
        double linearToGamma(double linearComp) const;

    public:
        void writeColor(std::ostream &out, color pixelCol, int sampPerPixel);
        void setAspectRatio(double rat);
        void setImgWidth(int width);
        void setSamples(int samp);
        void setRecuseLim(int lim);
        void setfov(int deg);
        void setCameraPos(point3 lkFrom, point3 lkAt, vec3 vecUp);
        void setDefocusAngle(double deg);
        void setFocusDist(double dist);
        void render(const hittable &objects);
};



#endif
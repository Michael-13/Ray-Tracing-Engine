#include "camera.h"

void camera::initialize() {
    imgHeight = static_cast<int>(imgWidth/aspectRatio);
    imgHeight = (imgHeight < 1) ? 1 : imgHeight;

    // viewport dimensions
    double theta = degToRad(fov);
    double h = tan(theta/2);
    double viewportHeight = 2.0 * h * focusDist;
    double viewportWidth = viewportHeight * (static_cast<double>(imgWidth)/imgHeight);
    cameraCentre = lookfrom;
    
    // Calculate the u,v,w unit basis vectors for the camera coordinate frame
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    // Axis vectors
    vec3 viewportU = viewportWidth * u; // Vector across the viewport horizontal ege
    vec3 viewportV = viewportHeight * -v; // Vector down viewport vertical edge

    // Delta vectors (distance between each pixel)
    pixelDeltaU = viewportU/imgWidth;
    pixelDeltaV = viewportV/imgHeight;

    // Upper left pixel
    point3 viewportUpperLeft = cameraCentre - (focusDist * w) - viewportU/2 - viewportV/2;
    pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    // Calculate the camera defocus disk basis vectors
    double defocusRadius = focusDist * tan(degToRad(defocusAngle/2));
    defocusDiskU = u * defocusRadius;
    defocusDiskV = v * defocusRadius;

}

color camera::rayColor(const ray &r, const hittable &obj, int count) {
    hitRecord hr;
    if (count >= recurseLim) {
        return color(0,0,0);
    }

    if (obj.hit(r, interval(0.001, infinity), hr)) {
        ray scattered;
        color attenuation;
        if (hr.mat->scatter(r, hr, attenuation, scattered)) {
            return attenuation * rayColor(scattered, obj, ++count);
        }
        return color(0,0,0);
    }
    

    // this is just the gradient in the background
    vec3 unitDir = unit_vector(r.direction());
    double a = 0.5*(unitDir.y() + 1.0);
    return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
}

point3 camera::defocusDiskSample() const {
    point3 p = randomInUnitDisk();
    return cameraCentre + (p[0] * defocusDiskU) + (p[1] * defocusDiskV);
}

ray camera::getRay(int u, int v) {
    point3 pixelCentre = pixel00Location + (u * pixelDeltaU) + (v * pixelDeltaV);
    // choose a random pixel in the unit square centred at pixelCentre
    point3 pixelSample = pixelCentre + pixelSampleSquare();

    point3 rayOrgin = (defocusAngle <= 0) ? cameraCentre : defocusDiskSample();
    vec3 rayDirection = pixelSample - rayOrgin;

    return ray(rayOrgin, rayDirection);
}

vec3 camera::pixelSampleSquare() const {
    // Returns a random point in the square surrounding a pixel at the orgin
    double px = -0.5 + random_double();
    double py = -0.5 + random_double();
    return (px * pixelDeltaU) + (py * pixelDeltaV);
}

double camera::linearToGamma(double linearComp) const {
    return sqrt(linearComp);
}

void camera::writeColor(std::ostream &out, color pixelCol, int sampPerPixel) {
    double r = pixelCol.x();
    double g = pixelCol.y();
    double b = pixelCol.z();

    // Divide the color by the number of samples
    double scale = 1.0 / sampPerPixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // apply gamma 2 transformation
    r = linearToGamma(r);
    g = linearToGamma(g);
    b = linearToGamma(b);

    static const interval intensity(0.000, 0.999);
    std::cout << static_cast<int>(256 * intensity.clamp(r)) << ' '
              << static_cast<int>(256 * intensity.clamp(g)) << ' '
              << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

void camera::setAspectRatio(double rat) {
    aspectRatio = rat;
}

void camera::setImgWidth(int width) {
    imgWidth = width;
}

void camera::setSamples(int samp) {
    samplesPerPixel = samp;
}

void camera::setRecuseLim(int lim) {
    recurseLim = lim;
}

void camera::setfov(int deg) {
    fov = deg;
}

void camera::setCameraPos(point3 lkFrom, point3 lkAt, vec3 vecUp) {
    lookfrom = lkFrom;
    lookat = lkAt;
    vup = vecUp;
}

void camera::setDefocusAngle(double deg) {
    defocusAngle = deg;
}

void camera::setFocusDist(double dist) {
    focusDist = dist;
}

void camera::render(const hittable &objects) {
    initialize();

    std::cout << "P3\n" << imgWidth << " " << imgHeight << "\n255" << std::endl;

    for(int i = 0; i < imgHeight; ++i) {
        std::clog << "\rScanlines remaining: " << (imgHeight - i) << " " << std::flush;
        for(int j = 0; j < imgWidth; ++j) {
            color pixelColor(0,0,0);
            for (int sample = 0; sample < samplesPerPixel; ++sample) {
                ray r = getRay(j,i);
                pixelColor += rayColor(r, objects, 0);
            }
            writeColor(std::cout, pixelColor, samplesPerPixel);
        }
    }
    std::clog << "Done" << std::endl;

}
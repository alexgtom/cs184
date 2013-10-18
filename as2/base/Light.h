#ifndef LIGHT_H_
#define LIGHT_H_

#include <math.h>

#include "Vector.h"
#include "Color.h"
#include "LocalGeo.h"
#include "Ray.h"

class Light {
  public:
    // This is an abstract class that will generate a ray starting from
    // the position stored in local to the position of the
    // light source.
    virtual void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) = 0;
};

class PointLight : public Light {
  public:
    Point loc;
    Color color;

    PointLight(float x, float y, float z, float r, float g, float b) {
      loc = Point(x, y, z);
      color = Color(r, g, b);
    }
    
    void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) {
      *lray = Ray(local.pos, loc - local.pos);
      *lcolor = color;
    }
};

class DirectionalLight : public Light {
  public:
    Vector direction;
    Color color;

    DirectionalLight(float x, float y, float z, float r, float g, float b) {
      direction = Vector(x, y, z);
      color = Color(r, g, b);
    }

    void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) {
      *lray = Ray(local.pos, -direction, 0.0f, INFINITY);
      *lcolor = color;
    }
};

#endif

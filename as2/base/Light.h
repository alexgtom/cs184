#ifndef LIGHT_H_
#define LIGHT_H_

#include <math.h>

#include "Vector.h"
#include "Color.h"
#include "LocalGeo.h"
#include "Ray.h"

#define LIGHT_TYPE_POINT 1
#define LIGHT_TYPE_DIRECTIONAL 2

// start the light at a offset to avoid having the start point
// accidentally intersecting with the surface
#define LIGHT_OFFSET 0.001f

class Light {
  public:
    // This is an abstract class that will generate a ray starting from
    // the position stored in local to the position of the
    // light source.
    virtual void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) = 0;
    virtual int getLightType() = 0;
    virtual Point getLoc() = 0;
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
      *lray = Ray(local.pos, loc - local.pos , LIGHT_OFFSET, (loc - local.pos).mag());
      *lcolor = color;
    }

    int getLightType() {
      return LIGHT_TYPE_POINT;
    }
    Point getLoc() {
        return loc;
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
      *lray = Ray(local.pos, direction, LIGHT_OFFSET, INFINITY); 
      *lcolor = color;
    
    }

    int getLightType() {
      return LIGHT_TYPE_DIRECTIONAL;
    }
    Point getLoc() {
        return Point();
    }
};

#endif

#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include "LocalGeo.h"
#include "Brdf.h"
#include "Intersection.h"

class Primitive {
  public:
    virtual bool intersect(Ray& ray, float* thit, Intersection* in) = 0;
    virtual bool intersectP(Ray& ray) = 0;
    virtual void getBRDF(LocalGeo& local, BRDF* brdf) = 0;
};

#endif

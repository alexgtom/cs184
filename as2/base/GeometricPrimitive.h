#ifndef GEOMETRIC_PRIMITIVE_H_
#define GEOMETRIC_PRIMITIVE_H_

#include "Primitive.h"
#include "Transformation.h"
#include "Material.h"
#include "Shape.h"

class GeometricPrimitive : public Primitive {
  public:
    Transformation objToWorld, worldToObj;
    Shape* shape;
    Material* mat;

  bool intersect(Ray& ray, float* thit, Intersection* in)  {
    Ray oray = worldToObj.transform(ray);
    LocalGeo olocal;
    if (!shape->intersect(oray, thit, &olocal))
      return false;

    in->primitive = this;
    in->local = objToWorld * olocal;
    return true;
  }

  bool intersectP(Ray& ray) {
    Ray oray = worldToObj.transform(ray);
    return shape->intersectP(oray);
  }

  void getBRDF(LocalGeo& local, BRDF* brdf) {
    material->getBRDF(local, brdf);
  }
};


#endif

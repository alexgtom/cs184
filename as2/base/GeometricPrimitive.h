#ifndef GEOMETRIC_PRIMITIVE_H_
#define GEOMETRIC_PRIMITIVE_H_

#include "Primitive.h"
#include "Transformation.h"
#include "Material.h"
#include "Shape.h"
#include "Intersection.h"

class GeometricPrimitive : public Primitive {
  public:
    Transformation objToWorld, worldToObj;
    Shape* shape;
    Material* mat;

    GeometricPrimitive(Shape* shape, Transformation objToWorld, 
        Transformation worldToObj, Material* mat) {
      this->shape = shape;
      this->objToWorld = objToWorld;
      this->worldToObj = worldToObj;
      this->mat = mat;
    }

    bool intersect(Ray& ray, float* thit, Intersection* in)  {
      Ray oray = worldToObj * ray;
      LocalGeo olocal;
      if (!shape->intersect(oray, thit, &olocal))
        return false;

      in->primitive = this;
      in->local = objToWorld * olocal;
      return true;
    }

    bool intersectP(Ray& ray) {
      Ray oray = worldToObj * ray;
      return shape->intersectP(oray);
    }

    void getBRDF(LocalGeo& local, BRDF* brdf) {
      mat->getBRDF(local, brdf);
    }
};


#endif

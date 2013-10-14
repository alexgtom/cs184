#pragma once

#include "Ray.h"
#include "Primitive.h"

class RayTracer {
  public:
    Primitive *aggregate_primitive;
    RayTracer(Primitive *aggregate_primitive) {
      this->aggregate_primitive = aggregate_primitive;
    }

    Color trace(Ray& ray, int depth=0) {
      if (depth >= 1) {
        return Color(0, 0, 0);
      }

      Intersection in;
      float thit;

      if (!aggregate_primitive->intersect(ray, &thit, &in)) {
         // No intersection
         return Color(0, 0, 0);
       }

       return Color(1.0f, 0, 0);
      
      //// Obtain the brdf at intersection point
      //in.primitive->getBRDF(in.local, &brdf);
      //
      //// There is an intersection, loop through all light source
      //for (i = 0; i < #lights; i++) {
      //lights[i].generateLightRay(in.local, &lray, &lcolor);
      //
      //// Check if the light is blocked or not
      //if (!primitive->intersectP(lray))
      //// If not, do shading calculation for this
      //// light source
      //*color += shading(in.local, brdf, lray, lcolor);
      //}
      //
      //// Handle mirror reflection
      //if (brdf.kr > 0) {
      //reflectRay = createReflectRay(in.local, ray);
      //
      //// Make a recursive call to trace the reflected ray
      //trace(reflectRay, depth+1, &tempColor);
      //*color += brdf.kr * tempColor;
      ////}
    }
};

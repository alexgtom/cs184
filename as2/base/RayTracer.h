#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "Ray.h"
#include "Primitive.h"

class RayTracer {
  public:
    Primitive *aggregate_primitive;
    RayTracer(Primitive *aggregate_primitive) {
      this->aggregate_primitive = aggregate_primitive;
    }

    void trace(Ray& ray, Color* color) {

    }

    void trace(Ray& ray, int depth, Color* color) {
      //if (depth exceed some threshold) {
      //  Make the color black and return
      //}

      //if (!primitive.intersect(ray, &thit, &in) {
      //    // No intersection
      //    Make the color black and return
      //  }
      // Obtain the brdf at intersection point
      //in.primitive->getBRDF(in.local, &brdf);

      //// There is an intersection, loop through all light source
      //for (i = 0; i < #lights; i++) {
      //lights[i].generateLightRay(in.local, &lray, &lcolor);

      //// Check if the light is blocked or not
      //if (!primitive->intersectP(lray))
      //// If not, do shading calculation for this
      //// light source
      //*color += shading(in.local, brdf, lray, lcolor);
      //}

      //// Handle mirror reflection
      //if (brdf.kr > 0) {
      //reflectRay = createReflectRay(in.local, ray);

      //// Make a recursive call to trace the reflected ray
      //trace(reflectRay, depth+1, &tempColor);
      //*color += brdf.kr * tempColor;
      //}
    }
};

#endif

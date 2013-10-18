#pragma once

#include <vector>

#include "Ray.h"
#include "Primitive.h"
#include "Intersection.h"
#include "Brdf.h"
#include "Light.h"
#include "Color.h"

class RayTracer {
  public:
    Primitive *aggregate_primitive;
    vector <Light*> lights;
    Color ambient;

    RayTracer(Primitive *aggregate_primitive, vector<Light*> lights, Color ambient) {
      this->aggregate_primitive = aggregate_primitive;
      this->lights = lights;
    }

    void trace(Ray& ray, int depth, Color* color) {
      Intersection in;
      float thit;
      BRDF brdf;

      if (depth == 0) {
        // Make the color black and return
        *color = Color(0, 0, 0);
        return;
      }

      if (!aggregate_primitive->intersect(ray, &thit, &in)) {
        // No intersection
        *color = Color(0, 0, 0);
        return;
      }

      // Obtain the brdf at intersection point
      in.primitive->getBRDF(in.local, &brdf);

      // There is an intersection, loop through all light source
      for (int i = 0; i < lights.size(); i++) {
        Ray lray;
        Color lcolor;
        lights[i]->generateLightRay(in.local, &lray, &lcolor);

        // Check if the light is blocked or not
        if (!aggregate_primitive->intersectP(lray)) {
          // If not, do shading calculation for this
          // light source
          *color += shading(in.local, brdf, lray, lcolor);
        }
      }

      // Handle mirror reflection
      if (brdf.kr > 0) {
        Color tempColor;
        Ray reflectRay = createReflectRay(in.local, ray);

        // Make a recursive call to trace the reflected ray
        trace(reflectRay, depth-1, &tempColor);
        *color += brdf.kr * tempColor;
      }
    }

    Color shading(LocalGeo local, BRDF brdf, Ray lray, Color lcolor) {
    }

    Ray createReflectRay(LocalGeo local, Ray ray) {
    }
};

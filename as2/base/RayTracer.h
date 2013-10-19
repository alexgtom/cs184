#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

#include "Ray.h"
#include "Primitive.h"
#include "AggregatePrimitive.h"
#include "Intersection.h"
#include "Brdf.h"
#include "Light.h"
#include "Color.h"
#include "Scene.h"
#include "Camera.h"

using namespace std;

class RayTracer {
  public:
    AggregatePrimitive *aggregate_primitive;
    vector <Light*> lights;
    float constant;
    float linear;
    float quadratic;
    Camera camera;

    RayTracer(
        AggregatePrimitive *aggregate_primitive, 
        vector<Light*> lights, 
        float constant, 
        float linear,
        float quadratic,
        Camera camera
      ) {
      this->aggregate_primitive = aggregate_primitive;
      this->lights = lights;
      this->constant = constant;
      this->linear = linear;
      this->quadratic = quadratic;
      this->camera = camera;
    }

    void trace(Ray& ray, int depth, Color* color) {
      Intersection in;
      float thit;
      BRDF brdf;

      *color = Color(0, 0, 0);

      if (depth == 0) {
        // Make the color black and return
        return;
      }

      if (!aggregate_primitive->intersect(ray, &thit, &in)) {
        // No intersection
        return;
      }

      // Obtain the brdf at intersection point
      in.primitive->getBRDF(in.local, &brdf);
      
      // Add ambient color to objects
      *color += brdf.ka;
      *color += brdf.ke;

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
          //*color = Color(1, 0, 0);
        } else {
          //*color = Color(0, 1, 0);
        }
      }

      //// Handle mirror reflection
      //if (brdf.kr > 0) {
      //  Color tempColor;
      //  Ray reflectRay = createReflectRay(in.local, ray);

      //  // Make a recursive call to trace the reflected ray
      //  trace(reflectRay, depth-1, &tempColor);
      //  *color += brdf.kr * tempColor;
      //}
    }


    Color shading(LocalGeo local, BRDF brdf, Ray lray, Color lcolor) {
      Color intensity(0, 0, 0);
      Vector h = (camera.dir + lray.dir) / (camera.dir + lray.dir).mag();

      // add emission term
      float r = (lray.pos - local.pos).mag();
      // R
      // TODO: shadows V_i
      intensity.r += lcolor.r / (constant + linear * r + quadratic * r * r) * \
             (brdf.kd.r * max(local.normal.norm().dot(lray.dir), 0.0f) + \
              brdf.ks.r * pow(max(local.normal.norm().dot(h), 0.0f), brdf.kr));
    
      // G
      // TODO: shadows V_i
      intensity.g += lcolor.g / (constant + linear * r + quadratic * r * r) * \
             (brdf.kd.g * max(local.normal.norm().dot(lray.dir), 0.0f) + \
              brdf.ks.g * pow(max(local.normal.norm().dot(h), 0.0f), brdf.kr));
      // B
      // TODO: shadows V_i
      intensity.b += lcolor.b / (constant + linear * r + quadratic * r * r) * \
             (brdf.kd.b * max(local.normal.norm().dot(lray.dir), 0.0f) + \
              brdf.ks.b * pow(max(local.normal.norm().dot(h), 0.0f), brdf.kr));

      return intensity;
    }

    Ray createReflectRay(LocalGeo local, Ray ray) {
    }
};

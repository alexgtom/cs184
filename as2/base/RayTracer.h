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
    Color ambient;
    float constant;
    float linear;
    float quadratic;
    Camera camera;

    RayTracer(
        AggregatePrimitive *aggregate_primitive, 
        vector<Light*> lights, 
        Color ambient,
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
      Color intensity;
      float r = (lray.pos - local.pos).mag();
      Vector h = (camera.dir + lray.dir) / (camera.dir + lray.dir).mag();
      // R
      intensity.r = ambient.r + brdf.ka.r;
      for(int i = 0; i < lights.size(); i++) {
        // TODO: shadows V_i
        intensity.r += lcolor.r / (constant + linear * r + quadratic * r * r) * \
               (brdf.kd.r * max(local.normal.dot(lray.dir), 0.0f) + \
                brdf.ks.r * pow(max(local.normal.dot(h), 0.0f), brdf.kr));
      }
      
      // G
      intensity.g = ambient.g + brdf.ka.g;
      for(int i = 0; i < lights.size(); i++) {
        // TODO: shadows V_i
        intensity.g += lcolor.g / (constant + linear * r + quadratic * r * r) * \
               (brdf.kd.g * max(local.normal.dot(lray.dir), 0.0f) + \
                brdf.ks.g * pow(max(local.normal.dot(h), 0.0f), brdf.kr));
      }
      

      // B
      intensity.b = ambient.b + brdf.ka.b;
      for(int i = 0; i < lights.size(); i++) {
        // TODO: shadows V_i
        intensity.b += lcolor.b / (constant + linear * r + quadratic * r * r) * \
               (brdf.kd.b * max(local.normal.dot(lray.dir), 0.0f) + \
                brdf.ks.b * pow(max(local.normal.dot(h), 0.0f), brdf.kr));
      }

      return intensity;
    }

    Ray createReflectRay(LocalGeo local, Ray ray) {
    }
};

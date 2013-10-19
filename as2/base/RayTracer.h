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
#include "PixelOps.h"

using namespace std;

class RayTracer {
  public:
    AggregatePrimitive *aggregate_primitive;
    vector <Light*> lights;
    float constant;
    float linear;
    float quadratic;
    Camera camera;
    bool first_iter;

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
      first_iter = true;
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
      //*color += brdf.ke;
      if (first_iter) {
        *color += brdf.ka;
        first_iter = false;
      } 
      *color += brdf.ke;

      // There is an intersection, loop through all light source
      //cout << "num lights: " << lights.size() << endl;
      for (int i = 0; i < lights.size(); i++) {
        Ray lray;
        Color lcolor;
        //cout << lcolor << endl;
        lights[i]->generateLightRay(in.local, &lray, &lcolor);

        // Check if the light is blocked or not
        if (!aggregate_primitive->intersectP(lray)) {
          // If not, do shading calculation for this
          // light source
          *color += shading(in.local, brdf, lray, lcolor, lights[i]->getLightType());
          //*color = Color(1, 0, 0);
        } else {
          //*color = Color(0, 1, 0);
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


    //Color shading(LocalGeo local, BRDF brdf, Ray lray, Color lcolor, int light_type) {
    //  PixelOps po(local.normal.norm());
    //  po.kd = brdf.kd;
    //  po.ks = brdf.ks;
    //  po.ka = Color(0, 0, 0);
    //  po.kr = brdf.kr;

    //  if (light_type == LIGHT_TYPE_POINT) 
    //    po.renderPointLight(lray.dir, lcolor);
    //  else if (light_type == LIGHT_TYPE_DIRECTIONAL)
    //    po.renderDirectionalLight(lray.dir, lcolor);
    //  else {
    //    cerr << "Invalid light type" << endl;
    //  }

    //  return po.c;
    //}

    Color shading(LocalGeo local, BRDF brdf, Ray lray, Color lcolor, int light_type) {
      Color intensity(0, 0, 0);
      Vector h = (camera.dir.norm() + lray.dir.norm()) / (camera.dir.norm() + lray.dir.norm()).mag();

      // add emission term
      float r = (lray.pos - local.pos).mag();
      // R
      intensity.r += lcolor.r / (constant + linear * r + quadratic * r * r) * \
             (brdf.kd.r * max(local.normal.norm().dot(lray.dir.norm()), 0.0f) + \
              brdf.ks.r * pow(max(local.normal.norm().dot(h), 0.0f), brdf.kr));
    
      // G
      intensity.g += lcolor.g / (constant + linear * r + quadratic * r * r) * \
             (brdf.kd.g * max(local.normal.norm().dot(lray.dir.norm()), 0.0f) + \
              brdf.ks.g * pow(max(local.normal.norm().dot(h), 0.0f), brdf.kr));
      // B
      intensity.b += lcolor.b / (constant + linear * r + quadratic * r * r) * \
             (brdf.kd.b * max(local.normal.norm().dot(lray.dir.norm()), 0.0f) + \
              brdf.ks.b * pow(max(local.normal.norm().dot(h), 0.0f), brdf.kr));

      return intensity;
    }
    //Color shading(LocalGeo local, BRDF brdf, Ray lray, Color lcolor, int light_type) {
    //  Vector normal = local.normal;
    //  Vector light_direction = lray.dir;

    //  float normal_mag = normal.mag();
    //  float light_mag = light_direction.mag();


    //}

    Ray createReflectRay(LocalGeo local, Ray ray) {
      Vector d = ray.dir;
      Vector n = local.normal;
      return Ray(local.pos, d - n * (2.0f * d.dot(n)), 0.1f, INFINITY);
    }
};

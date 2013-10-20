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
    bool vis_light;
    
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
        vis_light = false;
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
        
        
        *color = brdf.ke;
        
        // There is an intersection, loop through all light source
        //cout << "num lights: " << lights.size() << endl;
        for (int i = 0; i < lights.size(); i++) {
            Ray lray;
            Color lcolor;
            
            lights[i]->generateLightRay(in.local, &lray, &lcolor);
            
            // Check if the light is blocked or not
            if (!aggregate_primitive->intersectP(lray)) {
                // If not, do shading calculation for this
                // light source
                *color += shading(in.local, brdf, lray, lcolor, lights[i]->getLightType(), lights[i]->getLoc());
               // *color += brdf.ka;
              //  *color += brdf.ke;
                //vis_light = true;
            } 
        }
        
        *color += brdf.ke;
        *color += brdf.ka;
        //if (lights.size() == 0 || !vis_light){
            //*color += brdf.ke;
        //}
       // *color += brdf.ka;
        
        // Handle mirror reflection
        if (brdf.kr > 0) {
            Color tempColor;
            Ray reflectRay = createReflectRay(in.local, ray);
            
            // Make a recursive call to trace the reflected ray
            trace(reflectRay, depth-1, &tempColor);
            *color += brdf.kr * tempColor;
        }
    }
    
    
    Color shading(LocalGeo local, BRDF brdf, Ray lray, Color lcolor, int light_type, Point light_loc) {
        Color intensity(0, 0, 0);
        Vector h = (camera.dir.norm() + lray.dir.norm()) / (camera.dir.norm() + lray.dir.norm()).mag();
        
        
        float c,l,q;
        if (light_type = LIGHT_TYPE_DIRECTIONAL){   //no attenuation
            c = 1;
            l = 0;
            q = 0;
        } else {
            c = constant;
            l = linear;
            q = quadratic;
        }
        // add attenuation term
        float r = (local.pos - light_loc).mag();

        // R
        intensity.r += lcolor.r / (c + l * r + q * r * r) * \
        (brdf.kd.r * max(local.normal.norm().dot(lray.dir.norm()), 0.0f) + \
         brdf.ks.r * pow(max(local.normal.norm().dot(h), 0.0f), brdf.kr));
        
        // G
        intensity.g += lcolor.g / (c + l * r + q * r * r) * \
        (brdf.kd.g * max(local.normal.norm().dot(lray.dir.norm()), 0.0f) + \
         brdf.ks.g * pow(max(local.normal.norm().dot(h), 0.0f), brdf.kr));
        // B
        intensity.b += lcolor.b / (c + l * r + q * r * r) * \
        (brdf.kd.b * max(local.normal.norm().dot(lray.dir.norm()), 0.0f) + \
         brdf.ks.b * pow(max(local.normal.norm().dot(h), 0.0f), brdf.kr));
        
        return intensity;
    }
    
    Ray createReflectRay(LocalGeo local, Ray ray) {
        Vector d = ray.dir;
        Vector n = local.normal;
        return Ray(local.pos, d - n * (2.0f * d.dot(n)), 0.1f, INFINITY);
    }
};





/**#pragma once

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

#define LIGHT_TYPE_POINT 1
#define LIGHT_TYPE_DIRECTIONAL 2

using namespace std;

class RayTracer {
  public:
    AggregatePrimitive *aggregate_primitive;
    vector <Light*> lights;
    vector <Primitive*> prims;
    float constant;
    float linear;
    float quadratic;
    Camera camera;
    bool first_iter;
    float maxdepth;
    bool no_light;

    RayTracer(
        AggregatePrimitive *aggregate_primitive, 
        vector<Light*> lights,
        float constant, 
        float linear,
        float quadratic,
        Camera camera,
              float maxDepth
      ) {
      this->aggregate_primitive = aggregate_primitive;
      this->lights = lights;
      this->constant = constant;
      this->linear = linear;
      this->quadratic = quadratic;
      this->camera = camera;
        this->maxdepth = maxdepth;
      first_iter = true;
        no_light = false;
    }

    void trace(Ray& ray, int depth, Color* color) {
        Intersection in;
      float thit;
      BRDF brdf;

      *color = Color(0, 0, 0);

      //if (depth == 0) {
        /// Make the color black and return
       // return;
      //}
        //if (depth > maxDepth);
    //}
    
      if (!aggregate_primitive->intersect(ray, &thit, &in)) {
        // No intersection
        return;
      }
        

      // Obtain the brdf at intersection point
      in.primitive->getBRDF(in.local, &brdf);
      
      // Add ambient color to objects
    //   *color += brdf.ka;
      //  *color += brdf.ke;
        
        
      // There is an intersection, loop through all light source
      //cout << "num lights: " << lights.size() << endl;
      for (int i = 0; i < lights.size(); i++) {
        Ray lray;
        Color lcolor;
        //cout << lcolor << endl;
          lights[i]->generateLightRay(in.local, &lray, &lcolor);
   
          //check if blocked
         if (!aggregate_primitive->intersectP(lray)) {
             cout << "visible light";
          // If not, do shading calculation for this
          // light source
         *color += shading(in.local, brdf, lray, lcolor, lights[i]->getLightType(), lights[i]->getLoc());
         
           if (first_iter) {
            *color += brdf.ka;
            first_iter = false;
           }
         }else {
               no_light = true;
           
         
          //*color = Color(1, 0, 0);
          
         }
      }
        if (lights.size() == 0 || no_light) {
            *color += brdf.ke;
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

    Color shading(LocalGeo local, BRDF brdf, Ray lray, Color lcolor, int light_type, Point light_loc) {
      Color intensity(0, 0, 0);
      Vector h = (camera.dir.norm() + lray.dir.norm()) / (camera.dir.norm() + lray.dir.norm()).mag();
     //   Vector h = (lray.dir - camera.dir) / (lray.dir - camera.dir).mag();
   // h = h.norm();
        
        float c,l,q;
        if (light_type = LIGHT_TYPE_DIRECTIONAL){   //no attenuation
            c = 1;
            l = 0;
            q = 0;
        } else {
            c = constant;
            l = linear;
            q = quadratic;
        }
      // add attenuation term
      float r = (local.pos - light_loc).mag();
      // R
      intensity.r += lcolor.r / (c + l * r + q * r * r) * \
             (brdf.kd.r * max(local.normal.norm().dot(lray.dir.norm()), 0.0f) + \
              brdf.ks.r * pow(max(local.normal.norm().dot(h), 0.0f), brdf.kr));
    
      // G
      intensity.g += lcolor.g / (c + l * r + q * r * r) * \
             (brdf.kd.g * max(local.normal.norm().dot(lray.dir.norm()), 0.0f) + \
              brdf.ks.g * pow(max(local.normal.norm().dot(h), 0.0f), brdf.kr));
      // B
      intensity.b += lcolor.b / (c + l * r + q * r * r) * \
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
};**/

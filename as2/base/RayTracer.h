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
    int maxdepth;
    bool first_iter;
   // int depth;
    
    RayTracer(
              AggregatePrimitive *aggregate_primitive,
              vector<Light*> lights,
              float constant,
              float linear,
              float quadratic,
              Camera camera,
              int maxdepth
              ) {
        this->aggregate_primitive = aggregate_primitive;
        this->lights = lights;
        this->constant = constant;
        this->linear = linear;
        this->quadratic = quadratic;
        this->camera = camera;
        this->maxdepth = maxdepth;
        first_iter = true;
    }
    
    void trace(Ray& ray, int depth, Color* color) {
        Intersection in;
        float thit;
        BRDF brdf;
        
        *color = Color(0, 0, 0);
        
        if (depth > maxdepth) {
            // Make the color black and return
            return;
        }
        
        if (!aggregate_primitive->intersect(ray, &thit, &in)) {
            // No intersection
            return;
        }
        
        // Obtain the brdf at intersection point
        in.primitive->getBRDF(in.local, &brdf);
       
        
        //if (first_iter) {
            *color += brdf.ka;
          //  first_iter = false;
       // }
        
        *color += brdf.ke;
        
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
     
            }
         
        }

        // Handle mirror reflection
        if (brdf.ks.r > 0 || brdf.ks.g > 0 || brdf.ks.b > 0) {
       // if (brdf.kr > 0) {
        Color tempColor;
            Ray reflectRay = createReflectRay(in.local, ray);
            
            // Make a recursive call to trace the reflected ray
            trace(reflectRay, depth+1, &tempColor);
            *color += brdf.ks * tempColor;
        }
    }
    
    
    Color shading(LocalGeo local, BRDF brdf, Ray lray, Color lcolor, int light_type, Point light_loc) {
        Color intensity(0, 0, 0);
        
        float c,l,q,r;
        if (light_type = LIGHT_TYPE_DIRECTIONAL){   //no attenuation
            c = 1;
            l = 0;
            q = 0;
            r = 0;
        } else {
            c = constant;
            l = linear;
            q = quadratic;
            r = (local.pos - light_loc).mag();
        }
        
        //SET REFLECTION
        Vector d = lray.dir.norm();
        Vector n = local.normal.norm();
        Vector reflection = (n * 2 * (d.dot(n))) - d;
        reflection = -reflection.norm();
        
        //SET VIEWER
        Vector viewer = (camera.obj_pos - camera.cam_pos).norm();
        
        
        //NOT HALF ANGLE
        // R
        intensity.r += lcolor.r / (c + l * r + q * r * r) * \
         (brdf.kd.r * max(local.normal.norm().dot(lray.dir.norm()), 0.0f) + \
         brdf.ks.r * pow(max(reflection.dot(viewer), 0.0f), brdf.kr));
         
         // G
         intensity.g += lcolor.g / (c + l * r + q * r * r) * \
         (brdf.kd.g * max(local.normal.norm().dot(lray.dir.norm()), 0.0f) + \
         brdf.ks.g * pow(max(reflection.dot(viewer), 0.0f), brdf.kr));
         // B
         intensity.b += lcolor.b / (c + l * r + q * r * r) * \
         (brdf.kd.b * max(local.normal.norm().dot(lray.dir.norm()), 0.0f) +  \
         brdf.ks.b * pow(max(reflection.dot(viewer), 0.0f), brdf.kr));
        
        
        return intensity;
        
    }
    
    Ray createReflectRay(LocalGeo local, Ray ray) {
        Vector d = ray.dir.norm();
        Vector n = local.normal.norm();
        Vector reflection = d - (2.0 * (d.dot(n)) * n);
        reflection = reflection.norm();
        //Point start = local.pos + reflection;
        return Ray(local.pos, reflection, 0.1f, INFINITY);
    }
};





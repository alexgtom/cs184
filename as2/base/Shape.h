#ifndef SHAPE_H_
#define SHAPE_H_

#include <math.h>

#include "LocalGeo.h"
#include "Ray.h"
#include "Normal.h"

class Shape {
  public:
    // Test if ray intersects with the shape or not (in object space), if so,
    // return intersection point and normal
    virtual bool intersect(Ray& ray, float* thit, LocalGeo* local) = 0;

    // Same as intersect, but just return whether there is any intersection or
    // not
    virtual bool intersectP(Ray& ray) = 0;
};


class Sphere : public Shape {
  public:
    float radius;
    Sphere() {}
    Sphere(float radius) {
      this->radius = radius;
    }

    bool intersect(Ray& ray, float* thit, LocalGeo* local) {
      // Implemented sphere intersection equations from PBD pg. 117
      float A = ray.dir.x * ray.dir.x + 
                ray.dir.y * ray.dir.y + 
                ray.dir.z * ray.dir.z;
      float B = 2.0f * (
                  ray.dir.x * ray.pos.x +
                  ray.dir.y * ray.pos.y +
                  ray.dir.z * ray.pos.z);
      float C = ray.pos.x * ray.pos.x + 
                ray.pos.y * ray.pos.y + 
                ray.pos.z * ray.pos.z - radius * radius;
      float t0;
      float t1;

      quadraticSolver(A, B, C, &t0, &t1);

      if (t0 > ray.t_max || t1 < ray.t_min)
        return false;
      *thit = t0;
      if (t0 < ray.t_min) {
        *thit = t1;
        if (*thit > ray.t_max)
          return false;
      }
      
      // calculate intersection point
      local->pos.x = ray.pos.x + *thit * ray.dir.x;
      local->pos.y = ray.pos.y + *thit * ray.dir.y;
      local->pos.z = ray.pos.z + *thit * ray.dir.z;
      local->normal = Normal(local->pos.x, local->pos.y, local->pos.z);

      return true;
    }

    bool intersectP(Ray& ray) {
      float thit;
      LocalGeo local;
      return intersect(ray, &thit, &local);
    }

    //
    // A, B, and C are coefficients of the equation At^2 + Bt + C = 0
    // 
    // returns false if there is no solution, true otherwise with the solutions
    // in t0 and t1
    bool quadraticSolver(float A, float B, float C, float *t0, float *t1) {
      float sq_term = B * B - 4 * A * C;
      if (sq_term < 0)
        return false;
      
      *t0 = 0.5f * (-B - sqrt(sq_term)) / A;
      *t1 = 0.5f * (-B + sqrt(sq_term)) / A;

      return true;
    }
};


class Triange: public Shape {
  public:
    bool intersect(Ray& ray, float* thit, LocalGeo* local) {
    }

    bool intersectP(Ray& ray) {
    }
};

#endif

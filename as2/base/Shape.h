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
  // Origin is at the center of the sphere
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

    friend std::ostream& operator<< (std::ostream& stream, const Sphere& v) {
      stream << "Sphere(radius: " << v.radius << ")";
      return stream;
    }
};


class Triangle: public Shape {
  // Origin is at p0 with p0 on the x-axis and with p1 = ([0, +inf], [0, +inf])
  public:
    Point p0, p1, p2;
    Triangle() {}

    Triangle(Point p0, Point p1, Point p2) {
      this->p0 = p0;
      this->p1 = p1;
      this->p2 = p2;
    }

    bool intersect(Ray& ray, float* thit, LocalGeo* local) {
      // implements eq 3.5 from PBR on page 141
      Vector v_p0(p0.x, p0.y, p0.z);
      Vector v_p1(p1.x, p1.y, p1.z);
      Vector v_p2(p2.x, p2.y, p2.z);
      Vector v_ray_pos(ray.pos.x, ray.pos.y, ray.pos.z);

      Vector e1 = v_p1 - v_p0;
      Vector e2 = v_p2 - v_p0;
      Vector s = v_ray_pos - v_p0;

      Vector s1 = ray.dir.cross(e2);
      Vector s2 = s.cross(e1);
      
      float divisor = s1.dot(e1);
      float frac_term = 1.0f / divisor;

      if (divisor == 0.0f)
        return false;

      float t = frac_term * s2.dot(e2);
      float b1 = frac_term * s1.dot(s);
      if (b1 < 0.0f || b1 > 1.0f)
        return false;

      float b2 = frac_term * s2.dot(ray.dir);
      if (b2 < 0.0f || b1 + b2 > 1.0f)
        return false;
      
      if (t < ray.t_min || t > ray.t_max)
        return false;

      *thit = t;

      local->pos.x = ray.pos.x + t * ray.dir.x;
      local->pos.y = ray.pos.y + t * ray.dir.y;
      local->pos.z = ray.pos.z + t * ray.dir.z;
      local->normal = Normal(0, 0, 1);
      
      return true;
    }

    bool intersectP(Ray& ray) {
      float thit;
      LocalGeo local;

      return intersect(ray, &thit, &local);
    }

    friend std::ostream& operator<< (std::ostream& stream, const Triangle& v) {
      stream << "Triangle(p0: " << v.p0 << ", p1: " << v.p1 << ", p2: " << v.p2 << ")";
      return stream;
    }
};

#endif

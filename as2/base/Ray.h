#pragma once

#include "Vector.h"
#include "Point.h"

class Ray {
  public:
    Point pos;
    Vector dir;
    float t_min, t_max;
    Ray() {}
    Ray(Point pos, Vector dir, float t_min, float t_max) : 
      pos(pos), dir(dir), t_min(t_min), t_max(t_max) {}
    Ray(Point pos, Vector dir) : 
      pos(pos), dir(dir), t_min(0.0f), t_max(1.0f) {}
    Ray(const Ray& r) : 
      pos(r.pos), dir(r.dir), t_min(r.t_min), t_max(r.t_max) {}
    Ray& operator=(const Ray& r) {
      pos = r.pos;
      dir = r.dir;
      t_min = r.t_min;
      t_max = r.t_max;
      return *this;
    }
    ~Ray() {}

    bool operator==(const Ray& r) const {
      return pos==r.pos && dir==r.dir && t_min==r.t_min && t_max==r.t_max;
    }

    friend std::ostream& operator<< (std::ostream& stream, const Ray& r) {
      stream << "Ray( pos:" << r.pos << "  dir: " << r.dir;
      stream << "  trange: [" << r.t_min << ", " << r.t_max << "])";
      return stream;
    }
};

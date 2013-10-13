#pragma once

#include "Point.h"
#include "Sample.h"
#include "Sampler.h"
#include "Ray.h"
#include "Vector.h"

class Camera {
  public:
    Point pos;
    Vector dir;
    Vector up;
    Vector right;
    Camera() {}
    Camera(Point pos,
           Vector dir,
           Vector up)
    : pos(pos)
    , dir(dir.norm())
    , up(up.norm())
    , right(dir.cross(up).norm())
    {}
    Camera(const Camera& c) : pos(c.pos), dir(c.dir), up(c.up), right(c.right) {}
    Camera& operator=(const Camera& c) {
      pos = c.pos;
      dir = c.dir;
      up  = c.up;
      right = c.right;
      return *this;
    }
    ~Camera() {}

    Ray generateRay(const Sampler& sampler, const Sample& sample) {
      // these coordinates are in camera space
      // camera "window" is twice unit size centered on zero
      float x_coord = -1 + 2 * sample.x / sampler.width;
      float y_coord =  1 - 2 * sample.y / sampler.height;
      float z_coord =  1;

      // these are camera basis vectors in world space
      Vector x_hat = this->right;
      Vector y_hat = this->up;
      Vector z_hat = this->dir;

      // here we output a ray in world space
      return Ray(this->pos,
                 x_coord * this->right + y_coord * this->up + z_coord * this->dir,
                 1, 99999);
    }
};

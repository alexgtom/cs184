#pragma once

#include <iomanip>

#include "Point.h"
#include "Sample.h"
#include "Sampler.h"
#include "Ray.h"
#include "Vector.h"

class Camera {
  public:
    Point cam_pos;
    Point obj_pos;
    Vector dir;
    Vector up;
    Vector right;
    float fov;
    Camera() {}
    Camera(Point cam_pos, Point obj_pos, Vector up, float fov): 
      cam_pos(cam_pos), 
      obj_pos(obj_pos), 
      dir((obj_pos - cam_pos).norm()), 
      right((dir.cross(up)).norm()), 
      up((right.cross(dir)).norm()), 
      fov(fov) {}
    Camera(const Camera& c) : cam_pos(c.cam_pos), obj_pos(c.obj_pos), dir(c.dir), up(c.up), right(c.right), fov(c.fov) {}
    Camera& operator=(const Camera& c) {
      cam_pos = c.cam_pos;
      obj_pos = c.obj_pos;
      dir = c.dir;
      up  = c.up;
      right = c.right;
      fov = c.fov;
      return *this;
    }
    ~Camera() {}

    Ray generateRay(const Sampler& sampler, const Sample& sample) {
      float fov_radians   = fov * 3.1415926f / 180.0f;
      float vertical_size = 2.0f * tan(fov_radians/2.0f);
      float horiz_size    = vertical_size * sampler.width / sampler.height;

      // these coordinates are in camera space
      float x_coord = -0.5f *    horiz_size + horiz_size    * sample.x / sampler.width;
      float y_coord = -0.5f * vertical_size + vertical_size * sample.y / sampler.height;
      float z_coord = 1.0f;

      // these are camera basis vectors in world space
      Vector x_hat = this->right;
      Vector y_hat = this->up;
      Vector z_hat = this->dir;

      // here we output a ray in world space
      return Ray(this->cam_pos,
          x_coord * this->right + 
          y_coord * this->up + 
          z_coord * this->dir,
          1.0f, 99999.9f);
    }
};

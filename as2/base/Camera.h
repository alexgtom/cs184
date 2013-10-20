#pragma once

#include <iomanip>
#include <math.h>

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
    float fov; // degrees
    Camera() {}
    Camera(Point cam_pos, Point obj_pos, Vector up, float fov) {
      this->cam_pos = cam_pos;
      this->obj_pos = obj_pos;
      this->fov = fov;

      this->dir = (obj_pos - cam_pos).norm();
      //  this->dir = (cam_pos - obj_pos).norm();
      this->right = dir.cross(up).norm();
      this->up = up.norm();
    }
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
      float cam_to_obj_dist = (obj_pos - cam_pos).mag();
      float fov_y_radians   = fov * 3.1415926f / 180.0f;
      float vertical_size = 2.0f * cam_to_obj_dist * tan(fov_y_radians/2.0f);
      float horiz_size    = vertical_size * sampler.width / (float) sampler.height;
      float fov_x_radians   = 2.0f * atan(horiz_size / 2.0f / cam_to_obj_dist);

      // http://graphics.ucsd.edu/courses/cse168_s06/ucsd/CSE168_raytrace.pdf
      Vector e(cam_pos.x, cam_pos.y, cam_pos.z);
      Vector v = dir;
      Vector u = up;
      float fov_x = fov_x_radians;
      int width = sampler.width;
      int height = sampler.height;

      Vector c_x = v.cross(u) / (v.cross(u).mag() * v.cross(u).mag());
      Vector c_y = c_x.cross(v);
      float c_w = 2.0f * tan(fov_x/2.0f);
      float c_h = c_w / ((float) width / height);

      Point o = cam_pos;
      Vector d = v + c_x * ((sample.x/(float) width - 0.5f) * c_w) + c_y * ((sample.y/ (float) height - 0.5f) * c_h);

      return Ray(o, d, 0.0f, INFINITY);
    }
};

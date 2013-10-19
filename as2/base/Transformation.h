#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_

#include <Eigen/Dense>
#include <iostream>
#include <math.h>

#include "Vector.h"
#include "Point.h"
#include "Ray.h"
#include "Normal.h"
#include "LocalGeo.h"

using namespace std;

using namespace Eigen;

class Transformation {
  public:
    Matrix4f m;

    Transformation() {
      m = MatrixXf::Identity(4, 4);
    }

    Transformation(Matrix4f m) {
      this->m = m;
    }

    Transformation translate(float x, float y, float z) {
      Matrix4f t = MatrixXf::Identity(4, 4);
      t(0, 3) = x;
      t(1, 3) = y;
      t(2, 3) = z;
      m *= t;
      return *this;
    }

    Transformation rotate(float x, float y, float z, float angle) {
      Matrix4f t;
      Vector a = Vector(x, y, z).norm();
      float s = sinf(radians(angle));
      float c = cosf(radians(angle));

      t(0, 0) = a.x * a.x + (1.0f - a.x * a.x) * c;
      t(0, 1) = a.x * a.y * (1.0f - c) - a.z * s;
      t(0, 2) = a.x * a.z * (1.0f - c) + a.y * s;
      t(0, 3) = 0.0f;
      t(1, 0) = a.x * a.y * (1.0f - c) + a.z * s;
      t(1, 1) = a.y * a.y + (1.0f - a.y * a.y) * c;
      t(1, 2) = a.y * a.z * (1.0f - c) - a.x * s;
      t(1, 3) = 0.0f;
      t(2, 0) = a.x * a.z * (1.0f - c) - a.y * s;
      t(2, 1) = a.y * a.z * (1.0f - c) + a.x * s;
      t(2, 2) = a.z * a.z + (1.0f - a.z * a.z) * c;
      t(2, 3) = 0.0f;
      t(3, 0) = 0.0f;
      t(3, 1) = 0.0f;
      t(3, 2) = 0.0f;
      t(3, 3) = 1.0f;

      m *= t;
      return *this;
    }

    Transformation scale(float x, float y, float z) {
      Matrix4f t = MatrixXf::Identity(4, 4);
      t(0, 0) = x;
      t(1, 1) = y;
      t(2, 2) = z;

      m *= t;
      return *this;
    }

    Transformation inverse() {
      return Transformation(m.inverse());
    }

    Point operator*(const Point& p) {
      Vector4f v(p.x, p.y, p.z, 1.0f);
      Vector4f result = m * v;
      return Point(result(0), result(1), result(2)) / (float) p.w;
    }

    Vector operator*(const Vector& tv) {
      Vector4f v(tv.x, tv.y, tv.z, 0.0f);
      Vector4f result = m * v;
      return Vector(result(0), result(1), result(2));
    }

    Normal operator*(const Normal& n) {
      Vector4f v(n.x, n.y, n.z, n.w);
      Vector4f result = m.inverse().transpose() * v;
      return Normal(result(0), result(1), result(2));
    }

    Ray operator*(const Ray& r) {
      Ray ray(r);
      ray.pos = (*this) * r.pos;
      ray.dir = ((*this) * r.dir).norm();
      return ray;
    }

    LocalGeo operator*(const LocalGeo& l) {
      LocalGeo local_geo(l);
      local_geo.pos = (*this) * l.pos;
      local_geo.normal = (*this) * l.normal;
      return local_geo;
    }

    float radians(float degree) {
      return degree * 3.141592653589793 / 180.0;
    }

    Transformation operator*(const Transformation& t) {
      return Transformation(t.m * m);
    }
};

#endif

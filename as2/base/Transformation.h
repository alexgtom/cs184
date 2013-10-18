#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_

#include <Eigen/Dense>
#include <iostream>

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
};

#endif

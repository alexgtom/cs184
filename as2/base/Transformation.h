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

    Transformation() {}
    Transformation(Matrix4f m) {
      this->m = m;
    }

    Point operator*(const Point& p) {
      return p;
    }

    Vector operator*(const Vector& v) {
      return v;
    }

    Normal operator*(const Normal& n) {
      return n;
    }

    Ray operator*(const Ray& r) {
      return r;
    }

    LocalGeo operator*(const LocalGeo& l) {
      return l;
    }
};

#endif

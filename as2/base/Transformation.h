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

    Point transform(const Point& p) {
      return p;
    }

    Vector transform(const Vector& v) {
      return v;
    }

    Normal transform(const Normal& n) {
      return n;
    }

    Ray transform(const Ray& r) {
      return r;
    }

    LocalGeo transform(const LocalGeo& l) {
      return l;
    }
};

#endif

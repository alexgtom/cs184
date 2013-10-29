#ifndef BEZIER_PATCH_H_
#define BEZIER_PATCH_H_

#include <Eigen/Dense>

#include "BezierPatch.h"

using namespace Eigen;

class BezierPatch {
  public:
    // a 4 x 12 matrix containing the points making up the surface
    MatrixXf m; 

    BezierPatch(MatrixXf m) {
      this->m = m;
    }
};

#endif

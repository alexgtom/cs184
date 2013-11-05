#ifndef BEZIER_PATCH_H_
#define BEZIER_PATCH_H_

#include <glm/glm.hpp>

#include "BezierPatch.h"

using namespace glm;
using namespace std;

class BezierPatch {
  public:
    // the 16 points that make up the surface
    vector<vec3> points; 

    BezierPatch(vector<vec3> points) {
      this->points = points;
    }
};

#endif

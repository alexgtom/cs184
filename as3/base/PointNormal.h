#ifndef POINT_NORMAL_H_
#define POINT_NORMAL_H_

#include <glm/glm.hpp>

#include "BezierPatch.h"
#include "PointDeriv.h"

using namespace glm;
using namespace std;

class PointNormal {
 public:
  vec3 point;
  vec3 normal;


  PointNormal(vec3 p, vec3 n) {
    point = p;
    normal = n;
  }
};

#endif

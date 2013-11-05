#ifndef POINT_DERIV_H_
#define POINT_DERIV_H_

#include <glm/glm.hpp>

using namespace glm;
using namespace std;

class PointDeriv {

 public:
  vec3 point;
  vec3 derivative;

  PointDeriv(vec3 p, vec3 d) {
    point = p;
    derivative = d;
  }

  PointDeriv(vec3 p) {
    point = p;
  }
}

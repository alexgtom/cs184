#pragma once

#include "Vector.h"

// All Normal vectors are unit vectors
class Normal : public Vector {
  public:
    Normal() {}
    Normal(float x, float y, float z) : Vector(x, y, z) {
      // Converts Vector to Unit Vector for normal
      Vector n = norm();
      this->x = n.x;
      this->y = n.y;
      this->z = n.z;
    }
    Normal(const Normal& v) : Vector(v) {}
    ~Normal() {}
};

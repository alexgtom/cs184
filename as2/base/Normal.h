#pragma once

#include "Vector.h"

// All Normal vectors are unit vectors
class Normal : public Vector {
  public:
    Normal() {}
    Normal(float x, float y, float z) : Vector(x, y, z) {}
    Normal(const Normal& v) : Vector(v) {}
    ~Normal() {}

    friend std::ostream& operator<< (std::ostream& stream, const Normal& n) {
      stream << "Normal(" << n.x << ", " << n.y << ", " << n.z << ")";
      return stream;
    }
};

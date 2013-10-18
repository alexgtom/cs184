#ifndef BRDF_H_
#define BRDF_H_

#include "Color.h"

class BRDF {
  public:
    Color kd, ks, ka;
    float kr;

    BRDF() {}
    BRDF(Color kd, Color ks, Color ka, float kr) {
      this->kd = kd;
      this->ks = ks;
      this->ka = ka;
      this->kr = kr;
    }
};

#endif

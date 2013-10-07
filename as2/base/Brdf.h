#ifndef BRDF_H_
#define BRDF_H_

#include "Color.h"

class BRDF {
  public:
    Color kd, ks, ka, kr;

    BRDF() {}
    BRDF(Color kd, Color ks, Color ka, Color kr) {
      this->kd = kd;
      this->ks = ks;
      this->ka = ka;
      this->kr = kr;
    }
};

#endif

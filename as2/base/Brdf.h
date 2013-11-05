#ifndef BRDF_H_
#define BRDF_H_

#include "Color.h"

class BRDF {
  public:
    Color kd, ks, ke, ka;
    float kr;

    BRDF() {}
    BRDF(Color kd, Color ks, Color ke, Color ka, float kr) {
      this->kd = kd;
      this->ks = ks;
      this->ke = ke;
      this->kr = kr;
    this->ka = ka;
    }
};

#endif

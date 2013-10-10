#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Brdf.h"
#include "LocalGeo.h"

class Material {
  public:
    BRDF constantBRDF;

    void getBRDF(LocalGeo& local, BRDF* brdf) {
      *brdf = constantBRDF;
    }
};

#endif

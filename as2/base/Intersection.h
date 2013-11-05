#pragma once

#include "Primitive.h"
#include "LocalGeo.h"

class Primitive;

class Intersection {
  public:
    LocalGeo local;
    Primitive* primitive;
};

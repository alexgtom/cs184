#ifndef LOCALGEO_H_
#define LOCALGEO_H_

#include "Point.h"
#include "Normal.h"

class LocalGeo {
  public:
    Point pos;
    Normal normal;

    LocalGeo() {}
    LocalGeo(Point pos, Normal normal) {
      this->pos = pos;
      this->normal = normal;
    }
};

#endif

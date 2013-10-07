#ifndef LOCALGEO_H_
#define LOCALGEO

#include "Point.h"

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

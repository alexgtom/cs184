#ifndef SHAPE_H_
#define

class Shape {
  public:
    // Test if ray intersects with the shape or not (in object space), if so,
    // return intersection point and normal
    bool intersect(Ray& ray, float* thit, LocalGeo* local) = 0;

    // Same as intersect, but just return whether there is any intersection or
    // not
    bool intersectP(Ray& ray) = 0;
};


class Sphere : public Shape {
  bool intersect(Ray& ray, float* thit, LocalGeo* local) {
  }

  bool intersectP(Ray& ray) {
  }
};


class Triange: public Shape {
  bool intersect(Ray& ray, float* thit, LocalGeo* local) {
  }

  bool intersectP(Ray& ray) {
  }
};

#endif

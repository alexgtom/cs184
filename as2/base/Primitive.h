#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

class Primitive {
  public:
    virtual bool intersect(Ray& raym float* thit, LocalGeo* local) = 0;
    virtual bool intersectP(Ray& ray) = 0;
    virtual void getBRDF(LocalGeo& local, BRDF* brdf) = 0;
};

#endif

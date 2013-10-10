#ifndef AGGREGATE_PRIMITIVE_H_
#define AGGREGATE_PRIMITIVE_H_

#include <vector>

class AggregatePrimitive : public Primitive {
 public:
   AggregatePrimitive(vector<Primitive*> list) {
   }
   bool intersect(Ray& ray, float* thit, Intersection* in) {
   }

   bool intersectP(Ray& ray) {
   }

   void getBRDF(LocalGeo& local, BRDF* brdf) {
     exit(1);
     // This should never get called, because in->primitive will
     // never be an aggregate primitive
   }
}

#endif 

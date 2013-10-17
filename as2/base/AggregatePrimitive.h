#ifndef AGGREGATE_PRIMITIVE_H_
#define AGGREGATE_PRIMITIVE_H_

#include <vector>

#include "Primitive.h"

// Helper class for sorting primitives
class HelperPrimitive {
  public:
    float dist;
    float thit;
    bool intersect_result;
    Intersection in;

    HelperPrimitive(Ray ray, Primitive* primitive) {
      intersect_result = primitive->intersect(ray, &thit, &in);
      Point p = ray.pos - in.local.pos;
      dist = Vector(p.x, p.y, p.z).mag();
    }

	bool operator <(const HelperPrimitive& hp) const {
		return dist < hp.dist;
	}
};

class AggregatePrimitive : public Primitive {
  public:
    vector<Primitive*> list;

    AggregatePrimitive(vector<Primitive*> list) {
      this->list = list;
    }

    // thit is the thit to the closest shape that the ray hits
    bool intersect(Ray& ray, float* thit, Intersection* in) {
      if(list.size() == 0)
        return false;

      vector<HelperPrimitive> hp_list;

      for(int i = 0; i < list.size(); i++) {
        hp_list.push_back(HelperPrimitive(ray, list[i]));
      }
      
      // sort list in ascending order
      sort(hp_list.begin(), hp_list.end());
      
      // set thit and in
      // 0 is index of the closest shape
      *thit = hp_list[0].thit;
      *in = hp_list[0].in;
      return hp_list[0].intersect_result;
    }

    bool intersectP(Ray& ray) {
      float thit;
      Intersection in;
      return intersect(ray, &thit, &in);
    }

    void getBRDF(LocalGeo& local, BRDF* brdf) {
      exit(1);
      // This should never get called, because in->primitive will
      // never be an aggregate primitive
    }
};

#endif 

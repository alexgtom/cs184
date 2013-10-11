#ifndef AGGREGATE_PRIMITIVE_H_
#define AGGREGATE_PRIMITIVE_H_

#include <vector>

#include "Primitive.h"

// Helper class for sorting primitives
class HelperPrimitive {
  public:
    Primitive* primitive;
    float dist;

    HelperPrimitive(Ray ray, Primitive* primitive) {
      float thit;
      this->primitive = primitive;
      Intersection intersection;
      primitive->intersect(ray, &thit, &intersection);
      dist = Vector(ray.pos - intersection.local.pos).mag();
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
      
      // needed for sorting
      this->ray = ray;

      
      // sort list in ascending order
      sort(hp_list.begin(), hp_list.end());
      
      cout << "Sort: " << endl;
      for(int i = 0; i < hp_list.size(); i++) {
        cout << hp_list[i].dist << endl;
      }

      // set thit and in
      // 0 is index of the closest shape
      return hp_list[0].primitive->intersect(ray, thit, in);
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
  private:
    Ray ray;
};

#endif 

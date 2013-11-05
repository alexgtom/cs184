#ifndef AGGREGATE_PRIMITIVE_H_
#define AGGREGATE_PRIMITIVE_H_

#include <vector>

#include "Primitive.h"

// Helper class for sorting primitives
class HelperPrimitive {
  public:
    float dist;
    float thit;
    bool has_intersection;
    Intersection in;

    HelperPrimitive(Ray ray, Primitive* primitive) {
      has_intersection = primitive->intersect(ray, &thit, &in);
      dist = (ray.pos - in.local.pos).mag();
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
      // if theres no shapes, return false
      if(list.size() == 0)
        return false;

      vector<HelperPrimitive> hp_list;

      for(int i = 0; i < list.size(); i++) {
        if (list[i]->intersectP(ray))
          hp_list.push_back(HelperPrimitive(ray, list[i]));
      }

      // if theres no intersections, return false
      if (hp_list.size() == 0)
        return false;
      
      // sort list in ascending order
      sort(hp_list.begin(), hp_list.end());
      
      // set thit and in
      // 0 is index of the closest shape
      *thit = hp_list[0].thit;
      *in = hp_list[0].in;
      return hp_list[0].has_intersection;
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

    friend std::ostream& operator<< (std::ostream& stream, const AggregatePrimitive& v) {
      stream << "AggregatePrimitive[";
      for(int i = 0; i < v.list.size(); i++) {
        stream << "  [" << i << "]: " << v.list[i];
      }
      stream << "]";
      return stream;
    }
};

#endif 

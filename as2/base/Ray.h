#pragma once

#include "Vector.h"
#include "Point.h"

class Ray {
public:
	Point pos;
	Vector dir;
	float t_min, t_max;
    Ray() {}
	Ray(Point   pos, 
		Vector  dir, 
		float   t_min, 
		float   t_max) 
	: pos(pos)
	, dir(dir)
	, t_min(t_min)
	, t_max(t_max)
	{}
	Ray(const Ray& r) : pos(r.pos), dir(r.dir), t_min(r.t_min), t_max(r.t_max) {}
	Ray& operator=(const Ray& r) {
		pos = r.pos;
		dir = r.dir;
		t_min = r.t_min;
		t_max = r.t_max;
        return *this;
	}
	~Ray() {}

	bool operator==(const Ray& r) const {
		return pos==r.pos && dir==r.dir && t_min==r.t_min && t_max==r.t_max;
	}
};

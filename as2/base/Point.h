#pragma once

#include "Vector.h"

class Point : public Vector {
public:
    Point() {
    }

	Point(float x, float y, float z) : Vector(x, y, z) {
    }
	Point(const Vector& v) : Vector(v) { 
    }

	Point(const Point& p) : Vector(p) {
    }
};

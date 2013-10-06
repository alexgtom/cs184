#pragma once

#include "Vector.h"

class Point {
public:
	Vector v;
    Point() {}
	Point(float x, float y, float z) : v(x, y, z) {}
	Point(const Vector& v) : v(v) {}
	Point(const Point& p) : v(p.v) {}
	Point& operator=(const Point& p) {
		v = p.v;
	}
	~Point() {}

	bool operator==(const Point& p) const {
		return v == p.v;
	}

	Point operator+(const Vector& w) {
		return Point(v+w);
	}

	Point operator-(const Vector& w) {
		return Point(v-w);
	}
};

#pragma once

#include "Vector.h"

class Point {
  public:
    float x, y, z;

    Point() {
      x = y = z = 0;
    }

    Point(float x, float y, float z) {
      this->x = x;
      this->y = y;
      this->z = z;
    }
    Point(const Vector& v) { 
      x = v.x;
      y = v.y;
      z = v.z;
    }

    Point(const Point& p) {
      x = p.x;
      y = p.y;
      z = p.z;
    }

    Point& operator=(const Point& p) {
      x = p.x;
      y = p.y;
      z = p.z;
      return *this;
    }
    ~Point() {}

    bool operator==(const Point& p) const {
      return x == p.x && y == p.y && z == p.z;
    }

    Point operator+(const Vector& w) {
      return Point(x + w.x, y + w.y, z + w.z);
    }

    Point operator+(const Point& w) {
      return Point(x + w.x, y + w.y, z + w.z);
    }

    Point operator-(const Vector& w) {
      return Point(x - w.x, y - w.y, z - w.z);
    }

    Vector operator-(const Point& w) {
      return Vector(x - w.x, y - w.y, z - w.z);
    }
};

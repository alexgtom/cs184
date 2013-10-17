#pragma once

#include "Vector.h"

class Point {
  public:
    float x, y, z, w;

    Point() {
      x = y = z = 0;
      w = 1;
    }

    Point(float x, float y, float z) {
      this->x = x;
      this->y = y;
      this->z = z;
      this->w = 1;
    }
    Point(const Vector& v) { 
      x = v.x;
      y = v.y;
      z = v.z;
      w = 1;
    }

    Point(const Point& p) {
      x = p.x;
      y = p.y;
      z = p.z;
      w = p.w;
    }

    Point& operator=(const Point& p) {
      x = p.x;
      y = p.y;
      z = p.z;
      w = p.w;
      return *this;
    }
    ~Point() {}

    bool operator==(const Point& p) const {
      return x == p.x && y == p.y && z == p.z && w == p.w;
    }

    Point operator+(const Vector& v) {
      return Point(x + v.x, y + v.y, z + v.z);
    }

    Point operator-(const Vector& w) {
      return Point(x - w.x, y - w.y, z - w.z);
    }

    Point operator/(float c) {
      return Point(x/c, y/c, z/c);
    }

    Vector operator-(const Point& w) {
      return Vector(x - w.x, y - w.y, z - w.z);
    }

    friend std::ostream& operator<< (std::ostream& stream, const Point& p) {
      stream << "Point(" << p.x << ", " << p.y << ", " << p.z << ")";
    }
};

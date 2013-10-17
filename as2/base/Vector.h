#pragma once

#include <cmath>

class Vector {
public:
	float x, y, z, w;

	Vector(float x=0, float y=0, float z=0) : x(x), y(y), z(z) {
		w = 0;
	}
	Vector(const Vector& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
	Vector& operator=(const Vector& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = 0;
        return *this;
	}
	~Vector() {}

	bool operator==(const Vector& v) const {
		return x==v.x && y==v.y && z==v.z && w==v.w;
	}

	Vector operator*(const Vector& v) {
		return Vector(x * v.x, y * v.y, z * v.z);
	}

	Vector operator/(float d) {
		return Vector(x/d, y/d, z/d);
	}

	Vector operator+(const Vector& v) {
		return Vector(x + v.x, y + v.y, z + v.z);
	}

	Vector operator-() {
		return Vector(-x, -y, -z);
	}

	Vector operator-(const Vector& v) {
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	float sum() {
		return x + y + z;
	}

	float dot(const Vector& v) {
		return (*this * v).sum();
	}

	float mag() {
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

  Vector cross(const Vector& v) {
      // compute cross product using Sarrus' rule
      return Vector(Vector(y*v.z, z*v.x, x*v.y) - Vector(z*v.y, x*v.z, y*v.x));
  }

	Vector norm() {
		return *this / this->mag();
	}

    friend std::ostream& operator<< (std::ostream& stream, const Vector& v) {
      stream << "Vector(" << v.x << ", " << v.y << ", " << v.z << ")";
      return stream;
    }
};

	Vector operator*(float a, const Vector& v) {
		return Vector(a * v.x, a * v.y, a * v.z);
	}

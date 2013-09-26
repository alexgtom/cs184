#include <cmath>

class Vec3 {
public:
	float x, y, z;

	Vec3(float x=0, float y=0, float z=0) : x(x), y(y), z(z) {}
	Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
	Vec3& operator=(const Vec3& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}
	~Vec3() {}

	bool operator==(const Vec3& v) const {
		return x==v.x && y==v.y && z==v.z;
	}

	Vec3 operator*(const Vec3& v) {
		return Vec3(x * v.x, y * v.y, z * v.z);
	}

	Vec3 operator/(float d) {
		return Vec3(x/d, y/d, z/d);
	}

	Vec3 operator+(const Vec3& v) {
		return Vec3(x + v.x, y + v.y, z + v.z);
	}

	Vec3 operator-() {
		return Vec3(-x, -y, -z);
	}

	Vec3 operator-(const Vec3& v) {
		return Vec3(x - v.x, y - v.y, z - v.z);
	}

	float sum() {
		return x + y + z;
	}

	float dot(const Vec3& v) {
		return (*this * v).sum();
	}

	float mag() {
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	Vec3 norm() {
		return *this / this->mag();
	}
};

	Vec3 operator*(float a, const Vec3& v) {
		return Vec3(a * v.x, a * v.y, a * v.z);
	}
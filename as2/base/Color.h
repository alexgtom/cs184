#pragma once

#include <cmath>

class Color {
public:
	float r, g, b;

	Color(float r=0, float g=0, float b=0) : r(r), g(g), b(b) {}
	Color(const Color& c) : r(c.r), g(c.g), b(c.b) {}
	Color& operator=(const Color& c) {
		r = c.r;
		g = c.g;
		b = c.b;

        return *this;
	}
	~Color() {}

	bool operator==(const Color& c) const {
		return r==c.r && g==c.g && b==c.b;
	}

	Color operator*(const Color& c) {
		return Color(r * c.r, g * c.g, b * c.b);
	}

	Color operator/(float d) {
		return Color(r/d, g/d, b/d);
	}

	Color operator+(const Color& c) {
		return Color(r + c.r, g + c.g, b + c.b);
	}

	Color operator+=(const Color& c) {
		return Color(r+=c.r, g+=c.g, b+=c.b);
	}

	Color operator+=(float c) {
		return Color(r+=c, g+=c, b+=c);
	}

	Color operator-() {
		return Color(-r, -g, -b);
	}

	Color operator-(const Color& c) {
		return Color(r - c.r, g - c.g, b - c.b);
	}
    float getR(){
        return r;
    }
    float getG() {
        return g;
    }
    float getB() {
        return b;
    }

	float sum() {
		return r + g + b;
	}

    friend std::ostream& operator<< (std::ostream& stream, const Color& v) {
      stream << "Color(" << v.r << ", " << v.g << ", " << v.b << ")";
      return stream;
    }
};

Color operator*(float a, const Color& c) {
	return Color(a * c.r, a * c.g, a * c.b);
}

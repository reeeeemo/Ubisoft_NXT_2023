#pragma once
#include "Matrix.h"
#include "Math.h"

struct Point
{
	Point(float i_x, float i_y, float i_z, float i_w);
	Point(); // Default constructor

	// Overloads
	Point operator+(const Point&) const;
	Point operator-(const Point&) const;
	Point operator*(float scalar) const;
	Point operator*(const Matrix4&); // 4x4 Matrix
	Point operator/(float scalar) const;
	
	void operator+=(const Point&);
	void operator-=(const Point&);
	void operator*=(float scalar);
	void operator/=(float scalar);

	// Saves on memory! Yay, memory allocation!
	union {
		struct { float x, y, z, w; };
	};
};


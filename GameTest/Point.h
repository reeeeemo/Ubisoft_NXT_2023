#pragma once
#include "Matrix.h"
#include "Math.h"

struct CPoint
{
	CPoint(float i_x, float i_y, float i_z, float i_w);
	CPoint(); // Default constructor

	// Overloads
	CPoint operator+(const CPoint&) const;
	CPoint operator-(const CPoint&) const;
	CPoint operator*(float scalar) const;
	CPoint operator*(const Matrix4&); // 4x4 Matrix
	CPoint operator/(float scalar) const;
	
	void operator+=(const CPoint&);
	void operator-=(const CPoint&);
	void operator*=(float scalar);
	void operator/=(float scalar);

	// Saves on memory! Yay, memory allocation!
	union {
		struct { float x, y, z, w; };
	};
};


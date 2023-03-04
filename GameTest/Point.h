#pragma once
#ifndef __POINT_H__
#define __POINT_H__


struct CPoint
{
	CPoint(float i_x, float i_y, float i_z, float i_w);
	CPoint(); // Default constructor

	// Overloads
	CPoint operator+(const CPoint&) const;
	CPoint operator-(const CPoint&) const;
	CPoint operator*(float scalar) const;
	CPoint operator*(const CPoint&) const;
	CPoint operator/(float scalar) const;
	bool operator !=(const CPoint&) const;

	void operator+=(const CPoint&);
	void operator-=(const CPoint&);
	void operator -=(float scalar);
	void operator*=(float scalar);
	void operator/=(float scalar);

	// Saves on memory! Yay, memory allocation!
	union {
		struct { float x, y, z, w; };
	};
};


#endif //!__POINT_H__
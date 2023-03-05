#include "stdafx.h"
#include "Point.h"

CPoint::CPoint() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) // No values given.
{
}

CPoint::CPoint(float i_x, float i_y, float i_z, float i_w) : x(i_x), y(i_y), z(i_z), w(i_w) // Values given.
{ 
}

CPoint CPoint::operator+(const CPoint&point) const
{
	return CPoint{ x + point.x, y + point.y, z + point.z, 1 };
}

CPoint CPoint::operator-(const CPoint& point) const
{
	return CPoint{ x - point.x, y - point.y, z - point.z, 1 };
}

CPoint CPoint::operator*(float scalar) const
{
	return CPoint{ x * scalar, y * scalar, z * scalar, 1 };
}

CPoint CPoint::operator*(const CPoint& point) const
{
	return CPoint(x * point.x, y * point.y, z * point.z, 1);
}

CPoint CPoint::operator/(float scalar) const
{
	return CPoint{ x / scalar, y / scalar, z / scalar, 1 };
}

bool CPoint::operator!=(const CPoint& point) const
{
	if (point.x != x || point.y != y || point.z != z) {
		return true;
	}
	return false;
}

bool CPoint::operator<=(const CPoint& point) const
{
	if (x <= point.x && y <= point.y) {
		return true;
	}
}

void CPoint::operator+=(const CPoint& point)
{
	x += point.x;
	y += point.y;
	z += point.z;
}

void CPoint::operator -=(const CPoint& point)
{
	x -= point.x;
	y -= point.y;
	z -= point.z;
}

void CPoint::operator-=(float scalar)
{
	x -= scalar;
	y -= scalar;
	z = 0; // Let's not change this since we are only in 2D still.
}

void CPoint::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

void CPoint::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
}
#include "stdafx.h"
#include "Point.h"

Point::Point() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) // No values given.
{
}

Point::Point(float i_x, float i_y, float i_z, float i_w) : x(i_x), y(i_y), z(i_z), w(i_w) // Values given.
{ 
}

Point Point::operator+(const Point &point) const
{
	return Point { x + point.x, y + point.y, z + point.z, 1 };
}

Point Point::operator-(const Point& point) const 
{
	return Point { x - point.x, y - point.y, z - point.z, 1 };
}

Point Point::operator*(float scalar) const
{
	return Point { x * scalar, y * scalar, z * scalar, 1 };
}

Point Point::operator/(float scalar) const
{
	return Point{ x / scalar, y / scalar, z / scalar, 1 };
}

void Point::operator+=(const Point& point) 
{
	x += point.x;
	y += point.y;
	z += point.z;
}

void Point::operator -=(const Point& point) 
{
	x -= point.x;
	y -= point.y;
	z -= point.z;
}

void Point::operator*=(const float scalar) 
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

Point Point::operator*(const Matrix4& matrix)
{
	// Adding all components then multiplying.
	x = x * matrix.matrix[0][0] + y * matrix.matrix[1][0] + z * matrix.matrix[2][0] + matrix.matrix[3][0];
	y = x * matrix.matrix[0][1] + y * matrix.matrix[1][1] + z * matrix.matrix[2][1] + matrix.matrix[3][1];
	z = x * matrix.matrix[0][2] + y * matrix.matrix[1][2] + z * matrix.matrix[2][2] + matrix.matrix[3][2];
	float w = x * matrix.matrix[0][3] + y * matrix.matrix[1][3] + z * matrix.matrix[2][3] + matrix.matrix[3][3];

	// Perspective divide.
	if (w != 0.0f)
	{
		x /= w;
		y /= w;
		z /= w;
	}

	return Point(x, y, z, w);
}

void Point::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
}
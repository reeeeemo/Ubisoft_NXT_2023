#include "stdafx.h"
#include "Position.h"

/* Constructor */
CPosition::CPosition() : x(0.0f), y(0.0f), z(0.0f)
{ }

/* Sets position via 3 float values. */
void CPosition::SetPosition(float input_x, float input_y, float input_z)
{
	x = input_x;
	y = input_y;
	z = input_z;
}

/* Sets position via a CPoint, essentially the same thing as 3 float values. */
void CPosition::SetPosition(CPoint destination)
{
	SetPosition(destination.x, destination.y, destination.z);
}

CPoint CPosition::GetPosition() {
	return CPoint(x, y, z, 1.0f);
}


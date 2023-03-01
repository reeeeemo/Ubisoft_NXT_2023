#include "stdafx.h"
#include "Position.h"

/* Constructor */
CPosition::CPosition()
{
	position = CPoint(0, 0, 0, 1);
}

/* Sets position via 3 float values. */
void CPosition::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

/* Sets position via a CPoint, essentially the same thing as 3 float values. */
void CPosition::SetPosition(CPoint destination)
{
	SetPosition(destination.x, destination.y, destination.z);
}

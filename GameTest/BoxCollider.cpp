#include "stdafx.h"
#include "BoxCollider.h"

/* Initializes the box collider and makes the 2x2 square. */
CBoxCollider::CBoxCollider(CPoint point1, CPoint point2, CPoint point3, CPoint point4) : p1(point1), p2(point2), p3(point3), p4(point4)	
{}

/* Initializes the box collider but with all 0 values. */
CBoxCollider::CBoxCollider() : p1(CPoint()), p2(CPoint()), p3(CPoint()), p4(CPoint())
{}

std::array<CPoint, 4> CBoxCollider::GetPoints()
{
	return {p1, p2, p3, p4};
}


#pragma once
#ifndef __BOXCOLLIDER_H__
#define __BOXCOLLIDER_H__

#include <array>
#include "Point.h"

struct CBoxCollider
{
	CBoxCollider(CPoint point1, CPoint point2, CPoint point3, CPoint point4);
	CBoxCollider(); // Default constructor

	// Basically a 2x2 matrix that acts as the collider
	union
	{
		struct { CPoint p1, p2, p3, p4; };
	};
};


#endif //!__BOXCOLLIDER_H__
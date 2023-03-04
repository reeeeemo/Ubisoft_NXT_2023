#pragma once
#ifndef __GRIDPOSITION_H__
#define __GRIDPOSITION_H__

#include "Point.h"
#include "Math.h"

struct CGridPosition
{
	/*
	* Functions 
	*/
	CGridPosition();
	CPoint GetGridPosition();
	void SetGridPosition(CPoint destination);
	void SetGridPosition(float x, float y);

	union {
		struct { float row, col; };
	};
};

#endif // !__GRIDPOSITION_H__
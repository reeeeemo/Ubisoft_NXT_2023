#pragma once
#ifndef __POSITION_H__
#define __POSITION_H__

#include "Point.h"
#include "Math.h"

struct CPosition
{
	/*
	 *  Functions
	 */
	CPosition();
	void SetPosition(float x, float y, float z);
	void SetPosition(CPoint destination);
	CPoint GetPosition();
	 /*
	  *  Variables
	  */
	union {
		struct { int x, y, z;  };
	};
};

#endif // !__POSITION_H__
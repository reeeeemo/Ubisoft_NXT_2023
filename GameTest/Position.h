#pragma once
#ifndef __POSITION_H__
#define __POSITION_H__
#include "Point.h"

struct CPosition
{
	/*
	 *  Functions
	 */
	CPosition();
	void SetPosition(float x, float y, float z);
	void SetPosition(CPoint destination);
	 /*
	  *  Variables
	  */
	CPoint position = CPoint(0,0,0,1);
};

#endif // !__POSITION_H__
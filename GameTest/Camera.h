#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Point.h"

class CCamera
{
public:
	static void Init();
	static void Update();
	static CPoint GetPosition();
	static void SetPosition(CPoint pos);
	static CPoint DisplaceObject(CPoint objectToDisplace);


private:
	static CPoint position;
};

#endif //!__CAMERA_H__
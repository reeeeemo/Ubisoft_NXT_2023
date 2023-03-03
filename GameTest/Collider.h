#pragma once
#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "Point.h"
#include "BoxCollider.h"
#include "App/app.h"

class CCollider
{
public:
	/*
	 *  Functions
	 */
	void SetColliderVerticies(CPoint p1, CPoint p2, CPoint p3, CPoint p4);
	bool IsColliding(CBoxCollider otherCollider);
	bool IsColliding(float x, float y);
	void DebugDrawCollider() const;

	/*
	 *  Variables
	 */
	bool colliding = false;
	CBoxCollider collider;
private:

};

#endif //!__COLLIDER_H__


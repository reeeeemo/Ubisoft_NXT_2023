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
	void UpdateColliderVerticies(CPoint position, float width, float height);
	void UpdateColliderVerticiesWithoutDisplacement(CPoint position, float width, float height);
	void UpdateColliderVerticiesWithRadius(CPoint position, float width, float height, float radius, bool isVertical);
	CPoint GetOverlappingSide(CBoxCollider otherCollider, float width, float height);

	/*
	 *  Variables
	 */
	bool colliding = false;
	bool isTrigger = false; // Is it used for just triggering events / actions.
	CBoxCollider collider;
private:

};

#endif //!__COLLIDER_H__


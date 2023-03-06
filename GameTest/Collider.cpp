#include "stdafx.h"
#include "Collider.h"
#include "Camera.h"
#include "TileManager.h"
#include <limits>
#include <algorithm>


/* Using AABB Collision, seeing if one rectangle in another. */
bool CCollider::IsColliding(CCollider* otherCollider)
{
	/* If top left X (rect 1) is less than top right X (rect 2)
	 * If bottom right X (rect 1) is greater than bottom left X (rect 2)
	 * If bottom left Y (rect 1) is less than top right Y (rect 2)
	 * If top right Y (rect 1) is greater than bottom right Y (rect 2)
	 */ 
	if (collider.p2.x > otherCollider->collider.p1.x &&
		collider.p2.x < otherCollider->collider.p2.x &&
		collider.p3.y > otherCollider->collider.p4.y &&
		collider.p4.y < otherCollider->collider.p4.y)
	{
		colliding = true;
		otherCollider->colliding = true;
		return true;
	}

	if (collider.p2.x > otherCollider->collider.p2.x &&
		collider.p1.x < otherCollider->collider.p2.x &&
		collider.p3.y > otherCollider->collider.p4.y &&
		collider.p4.y < otherCollider->collider.p3.y)
	{
		colliding = true;
		otherCollider->colliding = true;
		return true;
	}
	
	otherCollider->colliding = false;
	colliding = false;
	return false;
}



/* Looking for the x and y coordinate inbetween the box collider. */
/* Also known as point vs rect collision. */
bool CCollider::IsColliding(float x, float y)
{
	if (collider.p1.x < x &&
		collider.p2.x > x &&
		collider.p1.y < y &&
		collider.p3.y > y)
	{
		colliding = true;
		return true;
	}
	colliding = false;
	return false;
}

/* Finds the distance between all sides of rect, if any are negative then return the collision. Only called when colliding, so we do not have to worry about checking that. */
CPoint CCollider::ReturnDistanceBetweenRects(CCollider* otherCollider)
{
	float distance = 1.0f;
	float tempX = 0.0f;
	float tempY = 0.0f;

	

	// Distance between left side of the rect.
	if (collider.p2.x > otherCollider->collider.p1.x && otherCollider->collider.p2.x > collider.p2.x) {
		distance = collider.p2.x - otherCollider->collider.p1.x;
		tempX = distance;
		otherCollider->isLeftColliding = true;
	}
	// Distance between right side of the rect
	if (collider.p1.x < otherCollider->collider.p2.x && otherCollider->collider.p2.x < collider.p2.x) {
		distance = collider.p1.x - otherCollider->collider.p1.x;
		tempX = distance;
		otherCollider->isLeftColliding = false;
	}

	// Distance between bottom (1st rect) hitting the top (2nd rect) of the rect
	if (collider.p3.y > otherCollider->collider.p4.y && collider.p4.y < otherCollider->collider.p4.y) {
		distance = collider.p3.y - otherCollider->collider.p4.y;

		tempY = distance;
		otherCollider->isBottomColliding = true;
	}

	// Distance between top (1st rect) hitting the bottom (2nd rect) of the rect
	if (collider.p4.y < otherCollider->collider.p3.y && collider.p3.y > otherCollider->collider.p4.y) {
		distance = otherCollider->collider.p3.y - collider.p4.y;
		tempY = distance;
		otherCollider->isBottomColliding = false;
	}

	return CPoint(tempX, tempY, 0.0f, 1.0f);
}

/* Draws the collision outline for debug view. */
void CCollider::DebugDrawCollider() const
{
	int r = 0.0f;;
	int g = 1.0f;
	int b = 0.0f;
	if (colliding)
	{
		r = 1.0f;
		g = 0.0f;
	}
	App::DrawLine(collider.p1.x, collider.p1.y, collider.p2.x, collider.p2.y, r, g, b);
	App::DrawLine(collider.p2.x, collider.p2.y, collider.p3.x, collider.p3.y, r, g, b);
	App::DrawLine(collider.p3.x, collider.p3.y, collider.p4.x, collider.p4.y, r, g, b);
	App::DrawLine(collider.p4.x, collider.p4.y, collider.p1.x, collider.p1.y, r, g, b);
	App::DrawLine(collider.p3.x, collider.p3.y, collider.p1.x, collider.p1.y, r, g, b);
	App::DrawLine(collider.p4.x, collider.p4.y, collider.p2.x, collider.p2.y, r, g, b);

}

void CCollider::UpdateColliderVerticies(CPoint position, float width, float height)
{
	CPoint displaced_position = CPoint(CCamera::DisplaceObject(position).x - TILE_SIZE / 2,
		CCamera::DisplaceObject(position).y - TILE_SIZE / 2, 0.0, 1.0f);
	SetColliderVerticies(displaced_position + CPoint(-width / 2.0, 0.0f, 0.0f, 1.0f), displaced_position + CPoint(width / 2.0, 0.0, 0.0, 1.0f),
		displaced_position + CPoint(0.0, height / 2.0, 0.0, 1.0f), displaced_position + CPoint(0.0, -height / 2.0, 0.0, 1.0f));
}


void CCollider::UpdateColliderVerticiesWithRadius(CPoint position, float width, float height, float radius, bool isVertical)
{
	if (isVertical) { // If we are making this rectangle on vertical axis.
		height *= radius;
		width *= radius;
	}
	else { // If we are making this rectangle on horizontal axis.
		width *= radius;
	}
	SetColliderVerticies(position + CPoint(-width / 2.0,0.0, 0.0f, 1.0f), position + CPoint(width / 2.0, 0.0, 0.0, 1.0f),
		position + CPoint(0.0, height / 2.0, 0.0, 1.0f), position + CPoint(0.0, -height / 2.0, 0.0, 1.0f));
	
}

/* Grabs the point of the side that is currently colliding with the edge. */
CPoint CCollider::GetOverlappingSide(CBoxCollider otherCollider, float width, float height)
{
	if (colliding) {
		// Check Top side to see if overlap
		if (collider.p2.y > otherCollider.p1.y &&
			collider.p2.y < otherCollider.p2.y) {
			return CPoint(collider.p2.x + width / 2.0f, collider.p2.y, 0.0, 1.0f);
		}
		// Check Bottom side to see if overlap
		if (collider.p1.y < otherCollider.p2.y &&
			collider.p1.y > otherCollider.p1.y) {
			return CPoint(collider.p1.x + width / 2.0f, collider.p1.y, 0.0, 1.0f);
		}
		// Check Right side to see if overlap
		if (collider.p3.x > otherCollider.p2.x &&
			collider.p3.x < otherCollider.p3.x) {
			return CPoint(collider.p3.x, collider.p3.y - height / 2.0f, 0.0, 1.0f);
		}
		// Check Left side to see if overlap
		if (collider.p2.x < otherCollider.p3.x &&
			collider.p2.x > otherCollider.p2.x) {
			return CPoint(collider.p2.x, collider.p2.y - height / 2.0f, 0.0, 1.0f);
		}
	}
	return CPoint();
}

void CCollider::SetColliderVerticies(CPoint p1, CPoint p2, CPoint p3, CPoint p4)
{
	collider.p1 = p1;
	collider.p2 = p2;
	collider.p3 = p3;
	collider.p4 = p4;
}

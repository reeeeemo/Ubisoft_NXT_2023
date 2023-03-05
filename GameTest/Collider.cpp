#include "stdafx.h"
#include "Collider.h"
#include "Camera.h"
#include "TileManager.h"
#include <limits>
#include <algorithm>


/* Using AABB Collision, seeing if one rectangle in another. */
bool CCollider::IsColliding(CBoxCollider otherCollider)
{
	/* If col1.x <= col2.x + col2.w
	 * If col1.x + col1.w >= col2.x
	 * If col1.y <= col2.y + col2.h
	 * If col1.y + col1.h >= col2.y
	 */ 
	if (collider.p2.x <= otherCollider.p2.x &&
		collider.p4.x >= otherCollider.p1.x &&
		collider.p1.y <= otherCollider.p3.y &&
		collider.p3.y >= otherCollider.p4.y)
	{
		colliding = true;
		return true;
	}
	
	colliding = false;
	return false;
}



/* Looking for the x and y coordinate inbetween the box collider. */
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

}

void CCollider::UpdateColliderVerticies(CPoint position, float width, float height)
{
	CPoint displaced_position = CPoint(CCamera::DisplaceObject(position).x - TILE_SIZE / 2,
		CCamera::DisplaceObject(position).y - TILE_SIZE / 2, 0.0, 1.0f);
	SetColliderVerticies(displaced_position + CPoint(-width / 2.0, -height / 2.0, 0.0f, 1.0f), displaced_position + CPoint(-width / 2.0, height / 2.0f, 0.0, 1.0f),
		displaced_position + CPoint(width / 2.0, height / 2.0, 0.0, 1.0f), displaced_position + CPoint(width / 2.0f, -height / 2.0, 0.0, 1.0f));
}

void CCollider::UpdateColliderVerticiesWithoutDisplacement(CPoint position, float width, float height)
{
	SetColliderVerticies(position + CPoint(-width / 2.0, -height / 2.0, 0.0f, 1.0f), position + CPoint(-width / 2.0, height / 2.0f, 0.0, 1.0f),
		position + CPoint(width / 2.0, height / 2.0, 0.0, 1.0f), position + CPoint(width / 2.0f, -height / 2.0, 0.0, 1.0f));
}

void CCollider::UpdateColliderVerticiesWithRadius(CPoint position, float width, float height, float radius, bool isVertical)
{
	if (isVertical) { // If we are making this rectangle on vertical axis.
		height *= radius;
	}
	else { // If we are making this rectangle on horizontal axis.
		width *= radius;
	}
	SetColliderVerticies(position + CPoint(-width / 2.0, -height / 2.0, 0.0f, 1.0f), position + CPoint(-width / 2.0, height / 2.0f, 0.0, 1.0f),
		position + CPoint(width / 2.0, height / 2.0, 0.0, 1.0f), position + CPoint(width / 2.0f, -height / 2.0, 0.0, 1.0f));
	
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

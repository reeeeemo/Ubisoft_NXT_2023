#include "stdafx.h"
#include "Collider.h"

/* Using AABB Collision, seeing if both box colliders are colliding. */
bool CCollider::IsColliding(CBoxCollider otherCollider)
{
	/* If col1.x < col2.x + col2.w
	 * If col1.x + col1.x > col1.x
	 * If col1.y < col2.y + col2.h
	 * If col1.y + col1.h > col2.y
	 */ 
	if (collider.p1.x < otherCollider.p2.x &&
		collider.p2.x > otherCollider.p1.x &&
		collider.p1.y < otherCollider.p3.y && 
		collider.p3.y > otherCollider.p1.y)
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

void CCollider::SetColliderVerticies(CPoint p1, CPoint p2, CPoint p3, CPoint p4)
{
	collider.p1 = p1;
	collider.p2 = p2;
	collider.p3 = p3;
	collider.p4 = p4;
}

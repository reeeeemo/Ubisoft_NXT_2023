#include "stdafx.h"
#include "Rigidbody.h"
#include "Math.h"

CRigidbody::CRigidbody()
{
	velocity = CPoint(0.0f,0.0f,0.0f,1.0f);
	//acceleration = 0.0;
	acceleration = CPoint(0.0f, 0.0f, 0.0f, 1.0f);
	mass = 5.0;
	drag = 1.0;
}

/* Adds a force onto the position and sends back a Point with the new position (Semi-implicit Euler integration!) */
CPoint CRigidbody::UpdateForce(CPoint position, float deltaTime)
{
	CPoint new_position = CPoint();

	new_position.x = position.x + velocity.x * deltaTime;
	new_position.y = position.y + velocity.y * deltaTime;

	return new_position;
}

/* Adding the force with a direction vector. */
void CRigidbody::AddForce(CPoint forceApplied, float deltaTime) {

	acceleration = forceApplied / mass;
	velocity += acceleration * deltaTime;
}

/* Slows down the velocity, so when we let go of a key we are not constanly moving */
void CRigidbody::Update(float deltaTime)
{
	if (velocity.x != 0.0f)
	{
		velocity.x /= 0.5f * deltaTime;
	}
	if (velocity.y != 0.0f)
	{
		velocity.y /= 0.5f * deltaTime;
	}
}

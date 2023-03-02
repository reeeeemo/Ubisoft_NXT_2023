#include "stdafx.h"
#include "Rigidbody.h"
#include "Math.h"

CRigidbody::CRigidbody()
{
	velocity = CPoint(0.0f,0.0f,0.0f,1.0f);
	//acceleration = 0.0;
	acceleration = CPoint(0.5f, 0.5f, 0.0f, 1.0f);
	mass = 1.0;
	drag = 1.0;
}

/* Adds a force onto the position and sends back a Point with the new position (Verlet Integration!) */
CPoint CRigidbody::AddForce(CPoint position, float deltaTime)
{
	CPoint new_position = CPoint{ 0,0,0,1.0f };

	new_position.x = position.x + velocity.x * (deltaTime + 0.5f * acceleration.x * (deltaTime * deltaTime));
	new_position.y = position.y + velocity.y * (deltaTime + 0.5f * acceleration.y * (deltaTime * deltaTime));

	return new_position;
}

/* Slows down the velocity, so when we let go of a key we are not constanly moving */
void CRigidbody::Update(float deltaTime)
{
	if (velocity.x != 0.0f)
	{
		velocity.x /= 0.9f * deltaTime;
	}
	if (velocity.y != 0.0f)
	{
		velocity.y /= 0.9f * deltaTime;
	}
}

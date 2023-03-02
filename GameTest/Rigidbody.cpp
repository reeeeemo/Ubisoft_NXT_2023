#include "stdafx.h"
#include "Rigidbody.h"
#include "Math.h"

CRigidbody::CRigidbody()
{
	velocity = CPoint(0.0f,0.0f,0.0f,1.0f);
	acceleration = 0.0;
	//acceleration = CPoint(1.0f, 0.0f, 0.0f, 1.0f);
	mass = 1.0;
}

/* Adds a force onto the position and sends back a Point with the new position (Verlet Integration!) */
CPoint CRigidbody::AddForce(CPoint position, float deltaTime)
{
	acceleration = Math::AbsValue(acceleration); // Making sure that acceleration is always positive
	if (acceleration > MAX_ACCELERATION) // Not letting acceleration go over the max!
	{
		acceleration = MAX_ACCELERATION;
	}

	const CPoint new_position = position + velocity * (deltaTime + 0.5 * acceleration * (deltaTime * deltaTime));
	return new_position;
}

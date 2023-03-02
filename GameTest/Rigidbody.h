#pragma once
#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__
#include "Point.h"

constexpr double MAX_ACCELERATION = 2.0f;

struct CRigidbody
{
	/*
	 * Functions
	 */
	CRigidbody();
	CPoint AddForce(CPoint position, float deltaTime);
	/*
	 * Variables
	 */
	CPoint velocity;
	double acceleration;
	double mass;

};

#endif // !__RIGIDBODY_H__
#pragma once
#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__
#include "Point.h"

constexpr double MAX_ACCELERATION = 0.5;

struct CRigidbody
{
	/*
	 * Functions
	 */
	CRigidbody();
	CPoint UpdateForce(CPoint position, float deltaTime);
	void AddForce(CPoint forceApplied, float deltaTime);
	void Update(float deltaTime);
	/*
	 * Variables
	 */
	CPoint velocity;
	CPoint acceleration;
	double mass;
	double drag;

};

#endif // !__RIGIDBODY_H__
#pragma once
#ifndef __BOMB_H__
#define __BOMB_H__

#include <array>
#include "ComponentManager.h"

enum EBombs {
	CLASSIC,
	NUM_BOMBS
};

class CBomb
{
public:
	/*
	*	Functions
 	*/
	CBomb() = default;
	virtual ~CBomb() = default;

	static void Init();
	static void PlaceBomb(CPoint position, CPoint mousePosition, EBombs bombType, float deltaTime);
	static void UpdateActiveBombs(float deltaTime);
	static void RenderActiveBombs();
	static void Exit();

protected:
	/*
	*	Functions
	*/
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void Execute() = 0;
	virtual void RenderExplosion() = 0;
	virtual void Update(float deltaTime) = 0;
	/*
	*	Variables
	*/

	static std::array<CBomb*, NUM_BOMBS> s_bombs;
	static ComponentManager<CPosition>& s_bombPositions;
	static ComponentManager<CEntityRenderer>& s_bombRenderers;
	static ComponentManager<CRigidbody>& s_bombRigidbodies;
	static ComponentManager<CCollider>& s_bombColliders;

	int id;
	float radius; // Radius of explosion, will be for all 4 ways 
	float damage;
	float timer; // Time until bomb blows up.
	bool isEnabled = false;
	bool hasExploded = false;
	bool stopMoving = false;
};

#endif //__BOMB_H__
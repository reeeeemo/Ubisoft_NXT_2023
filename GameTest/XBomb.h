#pragma once
#ifndef __XBOMB_H__
#define __XBOMB_H__

#include "Bomb.h"

class CXBomb : public CBomb
{
	/*
	*	Functions
	*/

	void OnEnter() override;
	void OnExit() override;
	void Execute() override;
	void RenderExplosion() override;
	void Update();


	/*
	*	Variables
	*/
	Entity leftCrossRect;
	Entity rightCrossRect;
};

#endif // __XBOMB_H__
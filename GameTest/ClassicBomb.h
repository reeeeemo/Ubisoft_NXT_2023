#pragma once
#ifndef __CLASSICBOMB_H__
#define __CLASSICBOMB_H__

#include "Bomb.h"

class CClassicBomb : public CBomb
{
	/*
	*	Functions
	*/

	void OnEnter() override;
	void OnExit() override;
	void Execute() override;
	void RenderExplosion() override;
	void Update() override;
	/*
	*	Variables
	*/
	Entity verticalRect;
	Entity horizontalRect;

};

#endif //!__CLASSICBOMB_H__
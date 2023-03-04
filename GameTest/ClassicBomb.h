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

	/*
	*	Variables
	*/

};

#endif //!__CLASSICBOMB_H__
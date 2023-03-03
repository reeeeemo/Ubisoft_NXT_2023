#pragma once
#ifndef __STARTBUTTON_H__
#define __STARTBUTTON_H__

#include "Button.h"

class CStartButton : public CButton
{
	/*
	 * Functions
	 */
	void OnEnter() override;
	void OnExit() override;
	void Execute() override;

	/*
	 * Variables
	 */
};

#endif //!__STARTBUTTON_H__
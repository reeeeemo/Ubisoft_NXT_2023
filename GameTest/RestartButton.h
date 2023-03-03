#pragma once
#ifndef __RESTARTBUTTON_H__
#define __RESTARTBUTTON_H__

#include "Button.h"

class CRestartButton : public CButton
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

#endif //!__RESTARTBUTTON_H__
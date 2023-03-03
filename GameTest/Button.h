#pragma once
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "App/app.h"
#include <array>

enum EButtons
{
	START,
	RESTART,
	NUM_BUTTONS
};

class CButton
{
public:
	/*
	 * Functions
	 */
	CButton() = default;
	virtual ~CButton() = default;

	static void Init();
	static void Update(float deltaTime);
	static void Render();
	static void Exit();
	static void CheckForMouseInput(CButton* buttonToCheck);

	/*
	 *  Variables
	 */
	static float mouseX;
	static float mouseY;
protected:
	/*
	 * Functions
	 */
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void Execute() = 0;
	/*
	 * Variables
	 */
	bool isClicked = false;
	bool isEnabled = false;
	static std::array<CButton*, NUM_BUTTONS> s_buttons;
	static std::array<CSimpleSprite*, NUM_BUTTONS> s_buttonTextures;
};

#endif //!__BUTTON_H__
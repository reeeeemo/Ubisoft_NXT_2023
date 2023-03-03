#include "stdafx.h"
#include "Button.h"

#include "StartButton.h"
#include "RestartButton.h"
#include "Scene.h"

// Static variables initialization
std::array<CButton*, NUM_BUTTONS> CButton::s_buttons;
std::array<CSimpleSprite*, NUM_BUTTONS> CButton::s_buttonTextures;
float CButton::mouseX;
float CButton::mouseY;

void CButton::Init()
{
	s_buttons[START] = new CStartButton;
	s_buttons[RESTART] = new CRestartButton;

	s_buttonTextures[START] = App::CreateSprite(".\\Assets\\PlayButton.bmp", 1 , 1);
	s_buttonTextures[START]->SetScale(1.0f);
	s_buttonTextures[RESTART] = App::CreateSprite(".\\Assets\\PlayButton.bmp", 1, 1);

	s_buttons[START]->isEnabled = true;
}

/* Checks for mouse movement and if the buttons that are currently active have been clicked. */
void CButton::Update(float deltaTime)
{
	for (int i = 0; i < NUM_BUTTONS; i++)
	{
		if (s_buttons[i]->isEnabled == true)
		{
			CheckForMouseInput(s_buttons[i]);
			s_buttonTextures[i]->Update(deltaTime);
		}
	}
}

/* Renders any buttons that are currently active. */
void CButton::Render()
{
	for(int i = 0; i < NUM_BUTTONS; i++)
	{
		if (s_buttons[i]->isEnabled == true)
		{
			s_buttonTextures[i]->SetPosition(600.0f, 600.0f);
			s_buttonTextures[i]->Draw();
		}
	}
}

/* Delete all buttons and re-allocate memory, since this is only called at the end of the program. */
void CButton::Exit()
{
	for (int i = 0; i < s_buttons.size() - 1; i++)
	{
		delete s_buttons[i];
		s_buttons[i] = nullptr;
	}
	for (int i = 0; i < s_buttonTextures.size() - 1; i++)
	{
		delete s_buttonTextures[i];
		s_buttonTextures[i] = nullptr;
	}
}

/* Gets mouse position and checks if it is within the boundaries of the button.*/
void CButton::CheckForMouseInput(CButton* buttonToCheck)
{
	App::GetMousePos(mouseX, mouseY);
}

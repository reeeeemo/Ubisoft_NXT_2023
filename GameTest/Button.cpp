#include "stdafx.h"
#include "Button.h"

#include "StartButton.h"
#include "Scene.h"

// Static variables initialization
std::array<CButton*, NUM_BUTTONS> CButton::s_buttons;
ComponentManager<CCollider>& CButton::s_buttonColliders = ComponentManager<CCollider>();
ComponentManager<CPosition>& CButton::s_buttonPositions = ComponentManager<CPosition>();
ComponentManager<CEntityRenderer>& CButton::s_buttonRenderers = ComponentManager<CEntityRenderer>();
float CButton::mouseX;
float CButton::mouseY;

/* Initializes everything related to buttons. */
void CButton::Init()
{
	s_buttons[START] = new CStartButton;
	s_buttons[START]->id = CreateEntity();

	// Creating components for each button (we don't need to check if they contain since they never existed before this.
	s_buttonColliders.Create(s_buttons[START]->id);
	s_buttonPositions.Create(s_buttons[START]->id);
	s_buttonRenderers.Create(s_buttons[START]->id);

	s_buttonRenderers.GetComponent(s_buttons[START]->id)->CreateEntitySprite(".\\Assets\\PlayButton.bmp", 1, 1);
	//s_buttonRenderers.GetComponent(s_buttons[RESTART]->id)->CreateEntitySprite(".\\Assets\\PlayButton.bmp", 1, 1);

	// Set Position and Collliders
	// We only need to call these once since technically we are not going to be moving the button positions (I hope nothing "magical" happens to them o_o)
	CPoint start_button_pos = CPoint(475, 400, 0.0f, 1.0f);
	//CPoint restart_button_pos = CPoint(300.0f, 600.0f, 0.0f, 1.0f);
	float buttonWidth = s_buttonRenderers.GetComponent(s_buttons[START]->id)->spriteWidth;
	float buttonHeight = s_buttonRenderers.GetComponent(s_buttons[START]->id)->spriteHeight;

	s_buttonColliders.GetComponent(s_buttons[START]->id)->SetColliderVerticies(start_button_pos, start_button_pos + CPoint(buttonWidth, 0.0f, 0.0f, 1.0f), 
		start_button_pos + CPoint(buttonWidth, buttonHeight, 0.0f, 1.0f), start_button_pos + CPoint(0.0f, buttonHeight, 0.0f, 1.0f));


	//buttonWidth = s_buttonRenderers.GetComponent(s_buttons[RESTART]->id)->spriteWidth;
	//buttonHeight = s_buttonRenderers.GetComponent(s_buttons[RESTART]->id)->spriteHeight;


	//s_buttonColliders.GetComponent(s_buttons[RESTART]->id)->SetColliderVerticies(restart_button_pos, restart_button_pos + CPoint(buttonWidth, 0.0f, 0.0f, 1.0f),
	//	restart_button_pos + CPoint(buttonWidth, buttonHeight, 0.0f, 1.0f), restart_button_pos + CPoint(0.0f, buttonHeight, 0.0f, 1.0f));

	s_buttonPositions.GetComponent(s_buttons[START]->id)->SetPosition(start_button_pos);
	//s_buttonPositions.GetComponent(s_buttons[RESTART]->id)->SetPosition(restart_button_pos);
}

/* Checks for mouse movement and if the buttons that are currently active have been clicked. */
void CButton::Update(float deltaTime)
{
	for (int i = 0; i < NUM_BUTTONS; i++)
	{
		if (s_buttons[i]->isEnabled == true)
		{
			CheckForMouseInput(s_buttons[i]);
			s_buttonRenderers.GetComponent(s_buttons[i]->id)->Update(deltaTime, 
				CPoint(s_buttonPositions.GetComponent(s_buttons[i]->id)->GetPosition().x + s_buttonRenderers.GetComponent(s_buttons[i]->id)->spriteWidth / 2.0,
					s_buttonPositions.GetComponent(s_buttons[i]->id)->GetPosition().y + s_buttonRenderers.GetComponent(s_buttons[i]->id)->spriteHeight / 2.0, 0.0, 1.0f), false);
			s_buttonColliders.GetComponent(s_buttons[i]->id)->IsColliding(mouseX, mouseY);

			if (s_buttonColliders.GetComponent(s_buttons[i]->id)->colliding == true) {
				if (App::IsKeyPressed(MK_LBUTTON)) { // Checking for left click if our mouse is colliding
					s_buttons[i]->Execute();
				}
			}
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
			if (true)
			{
				s_buttonRenderers.GetComponent(s_buttons[i]->id)->Render();
				//s_buttonColliders.GetComponent(s_buttons[i]->id)->DebugDrawCollider();
			}
		}
	}
}

/* Delete all buttons and re-allocate memory, since this is only called at the end of the program. */
void CButton::Exit()
{
	for (int i = 0; i < s_buttons.size() - 1; i++)
	{
		s_buttonColliders.Erase(s_buttons[i]->id);
		s_buttonPositions.Erase(s_buttons[i]->id);
		s_buttonRenderers.Erase(s_buttons[i]->id);

		delete s_buttons[i];
		s_buttons[i] = nullptr;
	}
}

/* Gets mouse position and checks if it is within the boundaries of the button.*/
void CButton::CheckForMouseInput(CButton* buttonToCheck)
{
	App::GetMousePos(mouseX, mouseY);
}

void CButton::EnableButton(EButtons button)
{
	s_buttons[button]->OnEnter();
	s_buttons[button]->isEnabled = true;
}

void CButton::DisableButton(EButtons button)
{
	s_buttons[button]->OnExit();
	s_buttons[button]->isEnabled = false;
}

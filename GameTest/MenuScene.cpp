#include "stdafx.h"
#include "MenuScene.h"

#include <string>



void CMenuScene::Update(float deltaTime)
{
	
}

void CMenuScene::Render()
{
	App::Print(370, 600, "BOMBERMAN LEARNS PHYSICS!");
	App::Print(370, 300, "INSTRUCTONS: ");
	App::Print(370, 225, "WASD to move");
	App::Print(370, 250, "Right click to shoot a bomb!");
	App::Print(370, 175, "Find the goal!");
}

void CMenuScene::HandleEvents(float deltaTime)
{
}

void CMenuScene::OnEnter()
{
	CButton::EnableButton(START);
}

void CMenuScene::OnExit() {
	
}

#include "stdafx.h"
#include "MenuScene.h"

#include <string>



void CMenuScene::Update(float deltaTime)
{
	
}

void CMenuScene::Render()
{
	
}

void CMenuScene::HandleEvents(float deltaTime)
{
	if (App::IsKeyPressed('1')) {
		CButton::DisableButton(START);
		CScene::ChangeScenes(MAIN);
	}
}

void CMenuScene::OnEnter()
{
	CButton::EnableButton(START);
}

void CMenuScene::OnExit() {
	
}

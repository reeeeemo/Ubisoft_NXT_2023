#include "stdafx.h"
#include "MenuScene.h"

void CMenuScene::Update()
{
}

void CMenuScene::Render()
{
	App::DrawQuad(-0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0, 0);
}

void CMenuScene::HandleEvents()
{
	if (App::IsKeyPressed('D')) {
		CScene::s_current_scene = s_scenes[MAIN];
	}
}

void CMenuScene::OnEnter()
{
	
}

void CMenuScene::OnExit() {

}

#include "stdafx.h"
#include "MainScene.h"

void CMainScene::Update(float deltaTime)
{
}

void CMainScene::Render()
{
	App::DrawQuad(-0.05f, -0.05f, 0.0f, -0.05f, 0.05f, 0.0f, 0.05f, 0.05f, 0.0f, 0.05f, -0.05f, 0.0f, 0, 1.0f, 0);
}

void CMainScene::HandleEvents()
{
	if (App::IsKeyPressed('2')) {
		CScene::s_current_scene = s_scenes[MAIN_MENU];
	}
}

void CMainScene::OnEnter()
{
	
}

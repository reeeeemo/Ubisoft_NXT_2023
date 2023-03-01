#include "stdafx.h"
#include "MenuScene.h"

#include <string>

void CMenuScene::Update()
{
}

void CMenuScene::Render()
{
	CPoint plr_position = s_positions.GetComponent(player)->position;
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
	// Initializing the player
	s_entities.push_back(player);
	if (!s_positions.Contains((player)))
	{
		s_positions.Create(player);
	}
}

void CMenuScene::OnExit() {

}

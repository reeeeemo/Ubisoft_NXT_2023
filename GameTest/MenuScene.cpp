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
	// Initializing the player
	const auto player = CreateEntity();
	s_entities.push_back(player);
	if (!s_positions.Contains((player)))
	{
		s_positions.Create(player);
	}
}

void CMenuScene::OnExit() {

}

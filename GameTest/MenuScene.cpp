#include "stdafx.h"
#include "MenuScene.h"

#include <string>

enum PlayerAnimationStates
{
	ANIM_IDLE,
	ANIM_WALK
};

void CMenuScene::Update(float deltaTime)
{
	s_renderers.GetComponent(player)->entitySprite->Update(deltaTime);
	if (App::IsKeyPressed('A'))
	{
		s_renderers.GetComponent(player)->entitySprite->SetAnimation(ANIM_WALK);
	} else
	{
		s_renderers.GetComponent(player)->entitySprite->SetAnimation(ANIM_IDLE);
	}
}

void CMenuScene::Render()
{
	CEntityRenderer* plr_renderer = s_renderers.GetComponent(player);

	plr_renderer->Render();

	CPoint plr_position = s_positions.GetComponent(player)->position;
	
	//App::DrawQuad(-0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0, 0);
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
	// Initializing the player components
	if (!s_positions.Contains((player)))
	{
		s_positions.Create(player);
	}
	if (!s_renderers.Contains(player))
	{
		s_renderers.Create(player);
	}

	// 
	CEntityRenderer* plr_renderer = s_renderers.GetComponent(player);

	plr_renderer->CreateEntitySprite(".\\Assets\\cow.bmp", 3, 2);
	plr_renderer->entitySprite->SetPosition(400.0f, 400.0f);

	plr_renderer->entitySprite->CreateAnimation(animationStates::ANIM_IDLE, 1.0f, {0, 1, 2});
	plr_renderer->entitySprite->CreateAnimation(animationStates::ANIM_WALK, 1.0f, { 3, 4});
	plr_renderer->entitySprite->SetAnimation(animationStates::ANIM_IDLE);
}

void CMenuScene::OnExit() {

}

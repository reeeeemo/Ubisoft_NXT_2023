#include "stdafx.h"
#include "MenuScene.h"

#include <string>

/* Staetes */
enum AnimationStates
{
	ANIM_IDLE,
	ANIM_WALK
};

void CMenuScene::Update(float deltaTime)
{
	for (Entity entity : s_entities) {
		if (s_renderers.Contains(entity))
		{
			const CPoint current_pos = s_positions.GetComponent(entity)->position;
			s_renderers.GetComponent(entity)->Update(deltaTime, current_pos);
			s_positions.GetComponent(entity)->SetPosition(s_rigidbodies.GetComponent(entity)->AddForce(current_pos, deltaTime));
			s_rigidbodies.GetComponent(player)->Update(deltaTime);
		}
	}
}

void CMenuScene::Render()
{
	for (Entity entity : s_entities)
	{
		s_renderers.GetComponent(entity)->Render();
	}
}

void CMenuScene::HandleEvents(float deltaTime)
{
	if (App::IsKeyPressed('1')) {
		CScene::s_current_scene = s_scenes[MAIN];
	}
	if (App::IsKeyPressed('W')) // If player presses the "up" key
	{
		s_renderers.GetComponent(player)->entitySprite->SetAnimation(ANIM_WALK);
		s_rigidbodies.GetComponent(player)->velocity += CPoint(0.0f, 0.1f, 0.0f, 1.0f);
	} else if (App::IsKeyPressed('S')) // If player presses the "down" key
	{
		s_renderers.GetComponent(player)->entitySprite->SetAnimation(ANIM_WALK);
		s_rigidbodies.GetComponent(player)->velocity -= CPoint(0.0f, 0.1f, 0.0f, 1.0f);
	}

	if (App::IsKeyPressed('A')) // If player presses the "left" key
	{
		s_renderers.GetComponent(player)->entitySprite->SetAnimation(ANIM_WALK);
		s_rigidbodies.GetComponent(player)->velocity -= CPoint(0.1f, 0.0f, 0.0f, 1.0f);
	}
	else if (App::IsKeyPressed('D')) // If player presses the "right" key
	{
		s_renderers.GetComponent(player)->entitySprite->SetAnimation(ANIM_WALK);
		s_rigidbodies.GetComponent(player)->velocity += CPoint(0.1f, 0.0f, 0.0f, 1.0f);
		
	}
	else
	{
		s_renderers.GetComponent(player)->entitySprite->SetAnimation(ANIM_IDLE);
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
	if (!s_rigidbodies.Contains(player))
	{
		s_rigidbodies.Create(player);
	}

	// Initializing player animations + setting position
	CEntityRenderer* plr_renderer = s_renderers.GetComponent(player);
	CPosition* plr_position = s_positions.GetComponent(player);

	plr_renderer->CreateEntitySprite(".\\Assets\\cow.bmp", 3, 2);

	plr_renderer->entitySprite->CreateAnimation(AnimationStates::ANIM_IDLE, 0.5f, {0, 1, 2});
	plr_renderer->entitySprite->CreateAnimation(AnimationStates::ANIM_WALK, 0.5f, { 3, 4});
	plr_renderer->entitySprite->SetAnimation(AnimationStates::ANIM_IDLE);

	s_positions.GetComponent(player)->SetPosition(400.0f, 400.0f, 0);
	plr_renderer->entitySprite->SetPosition(plr_position->position.x, plr_position->position.y);

}

void CMenuScene::OnExit() {
	int vectorIterator = 0;
	for (const Entity entity : s_entities)
	{
		s_renderers.GetComponent(entity)->OnDestroy();
		s_renderers.Erase(entity);
		s_positions.Erase(entity);

		s_entities.erase(s_entities.begin() + vectorIterator);
		vectorIterator++;
	}
}

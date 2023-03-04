#include "stdafx.h"
#include "MainScene.h"

#include <string>


void CMainScene::Update(float deltaTime)
{
	// Clamping speed.
	if (plrSpeed.x > 0.15f) {
		plrSpeed.x = 0.15f;
	}
	else if (plrSpeed.x < -0.15f) {
		plrSpeed.x = -0.15f;
	}
	if (plrSpeed.y > 0.15f) {
		plrSpeed.y = 0.15f;
	}
	else if (plrSpeed.y < -0.15f) {
		plrSpeed.y = -0.15f;
	}


	for (Entity entity : s_entities) {
		if (s_renderers.Contains(entity))
		{
			// Getting our current and next position.
			const CPoint current_pos = s_positions.GetComponent(entity)->GetPosition();
			CPoint new_pos = s_rigidbodies.GetComponent(entity)->UpdateForce(current_pos, deltaTime);

			s_rigidbodies.GetComponent(entity)->AddForce(plrSpeed, deltaTime);

			// Checking tile collision to see if we hit a wall.
			CPoint collidingSide = TileManager::CheckForTileCollision(s_colliders.GetComponent(entity)->collider,
			s_renderers.GetComponent(entity)->spriteWidth, s_renderers.GetComponent(entity)->spriteHeight);

			// Get direction from colliding side to the position of our character, and then add a impulse force.
			if (collidingSide != CPoint(0.0,0.0,0.0,1.0f)) {
				CPoint directionAwayFromWall = new_pos - collidingSide;
				s_rigidbodies.GetComponent(entity)->AddForce(directionAwayFromWall / 100.0f, deltaTime);
				//s_rigidbodies.GetComponent(entity)->AddForce(Math::Normalize(current_pos - collidingSide) * CPoint(-plrSpeed.x, -plrSpeed.y, 0.0f, 1.0f) * 2.0f, deltaTime);
			}

			new_pos = s_rigidbodies.GetComponent(entity)->UpdateForce(current_pos, deltaTime);


			s_positions.GetComponent(entity)->SetPosition(new_pos);
			s_gridPositions.GetComponent(entity)->SetGridPosition(new_pos);
			
			// Update all the components
			s_renderers.GetComponent(entity)->Update(deltaTime, s_positions.GetComponent(entity)->GetPosition());
			s_colliders.GetComponent(entity)->UpdateColliderVerticies(s_positions.GetComponent(entity)->GetPosition(), s_renderers.GetComponent(entity)->spriteWidth,
				s_renderers.GetComponent(entity)->spriteHeight);
			s_rigidbodies.GetComponent(entity)->Update(deltaTime);
		}
	}
}

void CMainScene::Render()
{
	TileManager::DrawTileMap();
	TileManager::DebugDrawTileMap();

	for (Entity entity : s_entities)
	{
		s_renderers.GetComponent(entity)->Render();
		s_colliders.GetComponent(entity)->DebugDrawCollider();
	}
	
}

void CMainScene::HandleEvents(float deltaTime)
{
	if (App::IsKeyPressed('2')) {
		CScene::ChangeScenes(MAIN_MENU);
	}
	
	if (!(s_renderers.Contains(player) && s_rigidbodies.Contains(player))) {
		return;
	}

	if (App::IsKeyPressed('W')) // If player presses the "up" key
	{
		plrSpeed.y += 0.01f;
	}
	else if (App::IsKeyPressed('S')) // If player presses the "down" key
	{
		plrSpeed.y -= 0.01f;
	}
	else {
		plrSpeed.y = 0.0f;
	}

	if (App::IsKeyPressed('A')) // If player presses the "left" key
	{
		plrSpeed.x -= 0.01f;
	}
	else if (App::IsKeyPressed('D')) // If player presses the "right" key
	{
		plrSpeed.x += 0.01f;
	}
	else {
		plrSpeed.x = 0.0f;
	}

}

void CMainScene::OnEnter()
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
	if (!s_colliders.Contains(player)) {
		s_colliders.Create(player);
	}
	if (!s_gridPositions.Contains(player)) {
		s_gridPositions.Create(player);
	}

	// Initializing player animations + setting position
	CEntityRenderer* plr_renderer = s_renderers.GetComponent(player);
	CPosition* plr_position = s_positions.GetComponent(player);

	plr_renderer->CreateEntitySprite(".\\Assets\\player.bmp", 1, 1);

	// Setting collider verticies for player
	s_colliders.GetComponent(player)->UpdateColliderVerticies(plr_position->GetPosition(), plr_renderer->spriteWidth,
		plr_renderer->spriteHeight);

	// Setting player position and building the tile map.
	s_positions.GetComponent(player)->SetPosition(400.0f, 400.0f, 0);
	plr_renderer->entitySprite->SetPosition(plr_position->x, plr_position->y);
	s_gridPositions.GetComponent(player)->SetGridPosition(400.0f, 400.0f);
	TileManager::BuildTileMap();
}

void CMainScene::OnExit() {
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
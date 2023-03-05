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


	


	// Moving all rigidbodies according to their forces and positions
	for (Entity entity : s_entities) {
		if (s_rigidbodies.Contains(entity))
		{


			// Getting our current and next position.
			const CPoint current_pos = s_positions.GetComponent(entity)->GetPosition();
			CPoint new_pos = s_rigidbodies.GetComponent(entity)->UpdateForce(current_pos, deltaTime);


			s_rigidbodies.GetComponent(entity)->AddForce(plrSpeed, deltaTime);

			// Checking tile collision to see if we hit a wall.
			CPoint collidingSide = TileManager::CheckForTileCollision(s_colliders.GetComponent(entity)->collider,
				s_renderers.GetComponent(entity)->spriteWidth, s_renderers.GetComponent(entity)->spriteHeight);



			// Get direction from colliding side to the position of our character, and then add a impulse force.
			if (collidingSide != CPoint(0.0, 0.0, 0.0, 1.0f)) {
				CPoint directionAwayFromWall = new_pos - collidingSide;
				s_rigidbodies.GetComponent(entity)->AddForce((directionAwayFromWall / 90.0f), deltaTime);
			}

			new_pos = s_rigidbodies.GetComponent(entity)->UpdateForce(current_pos, deltaTime);

			float spriteWidth = s_renderers.GetComponent(player)->spriteWidth;
			float spriteHeight = s_renderers.GetComponent(player)->spriteHeight;

			/*new_pos = CPoint(new_pos.x - CCamera::GetPosition().x + (APP_INIT_WINDOW_WIDTH - TILE_SIZE) / 2,
				new_pos.y - CCamera::GetPosition().y + ((APP_INIT_WINDOW_HEIGHT - TILE_SIZE) / 2), 0.0, 1.0f);*/

			s_colliders.GetComponent(entity)->UpdateColliderVerticies(new_pos, s_renderers.GetComponent(entity)->spriteWidth,
				s_renderers.GetComponent(entity)->spriteHeight);
			s_renderers.GetComponent(entity)->Update(deltaTime, new_pos);
			s_rigidbodies.GetComponent(entity)->Update(deltaTime);
			s_positions.GetComponent(entity)->SetPosition(new_pos);
			s_gridPositions.GetComponent(entity)->SetGridPosition(new_pos);

			//CCamera::SetPosition(new_pos);
			//CPoint camera_pos = CPoint(new_pos.x - APP_INIT_WINDOW_WIDTH / 2.0,
			//	new_pos.y - APP_INIT_WINDOW_HEIGHT / 2.0f, 0.0, 1.0f);

			//s_positions.GetComponent(playerCamera)->SetPosition(camera_pos);

			//if (camera_pos.x < 0) {
			//	camera_pos.x = 0;
			//}
			//if (camera_pos.x > LEVEL_WIDTH - APP_INIT_WINDOW_WIDTH) {
			//	camera_pos.x = LEVEL_WIDTH - APP_INIT_WINDOW_WIDTH;
			//}
			//if (camera_pos.y < 0) {
			//	camera_pos.y = 0;
			//}
			//if (camera_pos.y > LEVEL_HEIGHT - APP_INIT_WINDOW_HEIGHT) {
			//	camera_pos.y = LEVEL_HEIGHT - APP_INIT_WINDOW_HEIGHT;
			//}


			//s_positions.GetComponent(entity)->SetPosition(new_pos);
			//



			//
		
			//CPoint new_camera_displacement = CPoint(camera_pos.x - new_pos.x, 0.0, 0.0, 1.0f);
			//s_positions.GetComponent(playerCamera)->SetPosition(new_camera_displacement);
			//// Update all the components
			//
			//
			//
			//
		}

	}


	CCamera::Update();


	//// Setting camera positions to player position and adjusting camera / tiles.
	//CPoint camera_pos = CPoint(s_positions.GetComponent(player)->GetPosition().x - APP_INIT_WINDOW_WIDTH / 2.0f + s_renderers.GetComponent(player)->spriteWidth / 2.0f,
	//	s_positions.GetComponent(player)->GetPosition().y + s_renderers.GetComponent(player)->spriteHeight / 2.0f, 0.0, 1.0f);


	//if (camera_pos.x < -TILE_SIZE / 2.0f) {
	//	camera_pos.x = -TILE_SIZE / 2.0f;
	//}
	//else if (camera_pos.x > LEVEL_WIDTH - APP_INIT_WINDOW_WIDTH - TILE_SIZE / 2.0f) {
	//	camera_pos.x = LEVEL_WIDTH - APP_INIT_WINDOW_WIDTH - TILE_SIZE / 2.0f;
	//}
	//camera_pos.y = -TILE_SIZE / 2.0f;

	//s_renderers.GetComponent(player)->Update(deltaTime, s_positions.GetComponent(player)->GetPosition() - camera_pos);
	//
	//s_colliders.GetComponent(player)->UpdateColliderVerticies(s_positions.GetComponent(player)->GetPosition() - camera_pos, s_renderers.GetComponent(player)->spriteWidth, s_renderers.GetComponent(player)->spriteHeight);
	//
	//s_positions.GetComponent(playerCamera)->SetPosition(camera_pos);
	//
	////s_gridPositions.GetComponent(playerCamera)->SetGridPosition(camera_pos);
	//
	//TileManager::MoveTiles(s_positions.GetComponent(player)->GetPosition() - camera_pos);
	CCamera::SetPosition(s_positions.GetComponent(player)->GetPosition());
}

void CMainScene::Render()
{
	TileManager::DrawTileMap();
	TileManager::DebugDrawTileMap();

	for (Entity entity : s_entities)
	{
		if (s_renderers.Contains(entity) && s_colliders.Contains(entity)) {
			s_renderers.GetComponent(entity)->Render(s_positions.GetComponent(player)->GetPosition());
			s_colliders.GetComponent(entity)->DebugDrawCollider();
		}
	}
	
}

void CMainScene::HandleEvents(float deltaTime)
{
	if (App::IsKeyPressed('2')) {
		CScene::ChangeScenes(MAIN_MENU);
	}
	
	// Don't run anything past here if we don't got a rigidbody or renderer.
	if (!(s_renderers.Contains(player) && s_rigidbodies.Contains(player))) {
		return;
	}

	if (App::IsKeyPressed(MK_RBUTTON)) { // If player pressed the "right mouse button"
		CPoint mouse_pos = CPoint();
		App::GetMousePos(mouse_pos.x, mouse_pos.y);
		CBomb::PlaceBomb(s_positions.GetComponent(player)->GetPosition(), mouse_pos, EBombs::CLASSIC, deltaTime);
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
		if (plrSpeed.y >= 0.05f) {
			plrSpeed.y -= 0.05f;
		}
		else if (plrSpeed.y <= -0.05f) {
			plrSpeed.y += 0.05f;
		}
		else {
			plrSpeed.y = 0.0f;
		}
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
		if (plrSpeed.x >= 0.05f) {
			plrSpeed.x -= 0.05f;
		}
		else if (plrSpeed.x <= -0.05f) {
			plrSpeed.x += 0.05f;
		}
		else {
			plrSpeed.x = 0.0f;
		}
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
	TileManager::BuildTileMap();
	CPoint safePosition = CPoint(400.0f, 400.0f, 0.0f, 1.0f);//TileManager::FindSafePosition();

	s_positions.GetComponent(player)->SetPosition(safePosition);
	plr_renderer->entitySprite->SetPosition(plr_position->x, plr_position->y);
	plr_renderer->ChangeScale(0.7f);
	s_gridPositions.GetComponent(player)->SetGridPosition(safePosition);
	CCamera::Init();
}

void CMainScene::OnExit() {
	int vectorIterator = 0;
	for (const Entity entity : s_entities)
	{
		s_renderers.GetComponent(entity)->OnDestroy();
		s_renderers.Erase(entity);
		s_positions.Erase(entity);
		s_rigidbodies.Erase(entity);
		s_colliders.Erase(entity);
		s_gridPositions.Erase(entity);

		s_entities.erase(s_entities.begin() + vectorIterator);
		vectorIterator++;
	}

	TileManager::OnExit();
}
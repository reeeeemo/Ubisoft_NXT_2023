#include "stdafx.h"
#include "MainScene.h"

#include <string>



void CMainScene::Update(float deltaTime)
{
	TileManager::UpdateTileMap(deltaTime);

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

			CCamera::SetPosition(s_positions.GetComponent(player)->GetPosition() - CPoint(APP_INIT_WINDOW_WIDTH / 2.0f, APP_INIT_WINDOW_HEIGHT / 2.0f, 0.0, 1.0f));

			CCamera::Update();

			s_rigidbodies.GetComponent(entity)->AddForce(plrSpeed, deltaTime);

			// Checking tile collision to see if we hit a wall.
			CPoint collidingSide = TileManager::CheckForTileCollision(s_colliders.GetComponent(entity)->collider,
				s_renderers.GetComponent(entity)->spriteWidth, s_renderers.GetComponent(entity)->spriteHeight);



			// Get direction from colliding side to the position of our character, and then add a impulse force.
			if (collidingSide != CPoint(0.0, 0.0, 0.0, 1.0f)) {
				//new_pos = current_pos;
				CPoint directionAwayFromWall = new_pos - collidingSide;
				s_rigidbodies.GetComponent(entity)->AddForce((directionAwayFromWall * 0.0001), deltaTime);
			}

			
			new_pos = s_rigidbodies.GetComponent(entity)->UpdateForce(current_pos, deltaTime);



			float spriteWidth = s_renderers.GetComponent(player)->spriteWidth;
			float spriteHeight = s_renderers.GetComponent(player)->spriteHeight;

			s_renderers.GetComponent(entity)->Update(deltaTime, new_pos, true);

			s_rigidbodies.GetComponent(entity)->Update(deltaTime);
			s_positions.GetComponent(entity)->SetPosition(new_pos);
			s_gridPositions.GetComponent(entity)->SetGridPosition(new_pos);
			s_colliders.GetComponent(entity)->UpdateColliderVerticies(new_pos, s_renderers.GetComponent(entity)->spriteWidth,
				s_renderers.GetComponent(entity)->spriteHeight);

		}

	}

	
}

void CMainScene::Render()
{
	TileManager::DrawTileMap();
	TileManager::DebugDrawTileMap();

	for (Entity entity : s_entities)
	{
		if (s_renderers.Contains(entity) && s_colliders.Contains(entity)) {
			s_renderers.GetComponent(entity)->Render();
			s_colliders.GetComponent(entity)->DebugDrawCollider();
		}
	}
	if (current_bomb == EBombs::CLASSIC) {
		App::Print(800, 30, "Current Bomb: CLASSIC");
	}
	else {
		App::Print(800, 30, "Current Bomb: XBOMB");
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
		CBomb::PlaceBomb(s_positions.GetComponent(player)->GetPosition(), mouse_pos + CCamera::GetPosition(), current_bomb, deltaTime);
	}

	if (App::IsKeyPressed('1')) { // If player presses "1" on their keyboard
		current_bomb = EBombs::XBOMB;
	}
	if (App::IsKeyPressed('3')) { // If player presses "3" on their keyboard
		current_bomb = EBombs::CLASSIC;
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
	CPoint safePosition = TileManager::FindSafePosition();

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
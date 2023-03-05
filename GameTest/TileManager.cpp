#include "stdafx.h"
#include "TileManager.h"
#include "Camera.h"

/* Static variable initialization. */
ComponentManager<CPosition>& TileManager::s_tilePositions = ComponentManager<CPosition>();
ComponentManager<CTile>& TileManager::s_tiles = ComponentManager<CTile>();
ComponentManager<CCollider>& TileManager::s_tileColliders = ComponentManager<CCollider>();
ComponentManager<CEntityRenderer>& TileManager::s_tileRenderers = ComponentManager<CEntityRenderer>();
std::vector<Entity> TileManager::tile_entities;




TileManager::TileManager() 
{};

/* Builds the tile map */
void TileManager::BuildTileMap()
{
	for (int row = 0; row < ROW_NUM; ++row) {
		for (int col = 0; col < COL_NUM; ++col) {
			// Creates entity and all components for the specific tile.
			Entity tileEntity = CreateEntity();
			tile_entities.push_back(tileEntity);
			auto& tilePos = s_tilePositions.Create(tileEntity);
			auto& tileCol = s_tileColliders.Create(tileEntity);
			auto& tileRend = s_tileRenderers.Create(tileEntity);
			auto& tile = s_tiles.Create(tileEntity);
			
			// Sets tiles based on their position or a random variable.
			if (row == 0 || col == 0 || row == ROW_NUM - 1 || col == COL_NUM - 1) {
				tile.tile_type = ETileType::IMPASSABLE;
				tileRend.CreateEntitySprite(".\\Assets\\stone.bmp", 1, 1);
				tileCol.isTrigger = false;
			} else {
				int isObstacle = std::rand() % 3; // Random number between 0 or 2. Meant to lessen some obstacles

				if (!isObstacle) { // If value == 1, or 2.
					tile.tile_type = ETileType::BREAKABLE;
					tileRend.CreateEntitySprite(".\\Assets\\breakable.bmp", 1, 1);
					tileCol.isTrigger = false;
				}
				else { // If value == 0.
					tile.tile_type = ETileType::OPEN;
					tileRend.CreateEntitySprite(".\\Assets\\sand.bmp", 1, 1);
					tileCol.isTrigger = true;
				}
			}

			// Sets position of sprite and player, and collider verticies of tile.
			const CPoint tile_pos = CPoint(col * TILE_SIZE, row * TILE_SIZE, 0.0f, 1.0f);
			tile.SetGridPosition(col, row);
			tilePos.SetPosition(tile_pos);
			//tileCol.UpdateColliderVerticiesWithoutDisplacement(tile_pos + TILE_OFFSET, tileRend.spriteWidth, tileRend.spriteHeight);
			//tileCol.SetColliderVerticies(tile_pos, CPoint(tile_pos.x + TILE_SIZE, tile_pos.y, 0.0f, 1.0f),
			//	CPoint(tile_pos.x + TILE_SIZE, tile_pos.y + TILE_SIZE, 0.0, 1.0f), CPoint(tile_pos.x, tile_pos.y + TILE_SIZE, 0.0f, 1.0f));
			tileRend.entitySprite->SetPosition(tile_pos.x + TILE_SIZE / 2.0, tile_pos.y + TILE_SIZE / 2.0);
		}
	}
}

CPoint TileManager::FindSafePosition()
{
	for (auto entity : tile_entities) {
		if (s_tiles.GetComponent(entity)->tile_type == ETileType::OPEN) {
			return s_tilePositions.GetComponent(entity)->GetPosition() + TILE_OFFSET;
		}
	}
}

/* Displays the built tile map. */
void TileManager::DrawTileMap()
{
	for (auto entity : tile_entities) {
		if (s_tileRenderers.Contains(entity)) {
			CPoint tile_position = s_tilePositions.GetComponent(entity)->GetPosition();
			s_tileRenderers.GetComponent(entity)->Render();
		}
	}
}

/* Draws the tile map for debug purposes (just outlines of the squares). */
void TileManager::DebugDrawTileMap()
{
	for (auto entity : tile_entities) {
		if (s_tiles.Contains(entity)) {
			CTile* tile = s_tiles.GetComponent(entity); // Grab tile from entity vector.
			if (tile->tile_type == ETileType::IMPASSABLE || tile->tile_type == ETileType::BREAKABLE) {
				s_tileColliders.GetComponent(entity)->colliding = true;
			}
			s_tileColliders.GetComponent(entity)->DebugDrawCollider();
		}
	}
}

/* Updates tile map and it's colliders / sprites. */
void TileManager::UpdateTileMap(float deltaTime)
{
	for (auto entity : tile_entities) {
		if (s_tiles.Contains(entity)) {
			s_tileRenderers.GetComponent(entity)->Update(deltaTime, CCamera::DisplaceObject(s_tilePositions.GetComponent(entity)->GetPosition()), true);

			// Sets tile collider relative to how large the map and sprites are, and where the camera position is :)
			s_tileColliders.GetComponent(entity)->UpdateColliderVerticies(CCamera::DisplaceObject(
				CPoint(s_tilePositions.GetComponent(entity)->x + s_tileRenderers.GetComponent(entity)->spriteWidth / 2, 
					s_tilePositions.GetComponent(entity)->y + s_tileRenderers.GetComponent(entity)->spriteHeight / 2, 0.0, 1.0f)) - TILE_OFFSET, 
				s_tileRenderers.GetComponent(entity)->spriteWidth, s_tileRenderers.GetComponent(entity)->spriteHeight);

		}
	}
}

/* Checks where the position is relative to the grid and if it is colliding with a tile. Returns the point that is colliding with the tile if there is one */
CPoint TileManager::CheckForTileCollision(CBoxCollider col, float width, float height)
{
	for (auto entity : tile_entities) {
		if (s_tileColliders.Contains(entity)) {
			if (s_tileColliders.GetComponent(entity)->IsColliding(col)) {
				if (s_tileColliders.GetComponent(entity)->isTrigger == false) {
					return s_tileColliders.GetComponent(entity)->GetOverlappingSide(col, width, height);
				}
			}
			
		}
	}
	return CPoint();
}

/* This time, breaks the tiles that are colliding and changes them to "OPEN", so if they are type "BREAKABLE" */
void TileManager::BreakTileColliding(CBoxCollider col)
{
	for (auto entity : tile_entities) {
		if (s_tileColliders.GetComponent(entity)) {
			if (s_tileColliders.GetComponent(entity)->IsColliding(col) && s_tiles.GetComponent(entity)->tile_type == ETileType::BREAKABLE) {
				s_tiles.GetComponent(entity)->tile_type = ETileType::OPEN;
				s_tileRenderers.GetComponent(entity)->ChangeEntitySprite(".\\Assets\\sand.bmp", 1, 1, s_tilePositions.GetComponent(entity)->GetPosition() + TILE_OFFSET);
				s_tileColliders.GetComponent(entity)->isTrigger = true;
			}
		}
	}
}

/* When we are exiting the function. */
void TileManager::OnExit()
{
	for (auto entity : tile_entities) {
		s_tilePositions.Erase(entity);
		s_tiles.Erase(entity);
		s_tileColliders.Erase(entity);
		s_tileRenderers.Erase(entity);
	}
}

#include "stdafx.h"
#include "TileManager.h"

/* */
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
			
			// Sets tile type dependant on if the tiles are in the corner or not.
			if (row == 0 || col == 0 || row == ROW_NUM - 1) {
				tile.tile_type = ETileType::IMPASSABLE;
				tileRend.CreateEntitySprite(".\\Assets\\stone.bmp", 1, 1);
			}
			else {
				tile.tile_type = ETileType::OPEN;
				tileRend.CreateEntitySprite(".\\Assets\\sand.bmp", 1, 1);
			}

			// Sets position of sprite and player, and collider verticies of tile.
			const CPoint tile_pos = CPoint(col * TILE_SIZE, row * TILE_SIZE, 0.0f, 1.0f);
			tile.SetGridPosition(col, row);
			tilePos.SetPosition(tile_pos);
			tileCol.SetColliderVerticies(tile_pos, CPoint(tile_pos.x + TILE_SIZE, tile_pos.y, 0.0f, 1.0f),
				CPoint(tile_pos.x + TILE_SIZE, tile_pos.y + TILE_SIZE, 0.0, 1.0f), CPoint(tile_pos.x, tile_pos.y + TILE_SIZE, 0.0f, 1.0f));
			tileRend.entitySprite->SetPosition(tile_pos.x + TILE_SIZE / 2.0, tile_pos.y + TILE_SIZE / 2.0);
		}
	}
}

/* Displays the built tile map. */
void TileManager::DrawTileMap()
{
	for (auto entity : tile_entities) {
		if (s_tileRenderers.Contains(entity)) {
			s_tileRenderers.GetComponent(entity)->Render();
		}
	}
}

void TileManager::DebugDrawTileMap()
{
	for (auto entity : tile_entities) {
		if (s_tiles.Contains(entity)) {
			CTile* tile = s_tiles.GetComponent(entity); // Grab tile from entity vector.
			if (tile->tile_type == ETileType::IMPASSABLE) {
				s_tileColliders.GetComponent(entity)->colliding = true;
			}
			s_tileColliders.GetComponent(entity)->DebugDrawCollider();
		}
	}
}

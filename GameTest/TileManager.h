#pragma once
#ifndef __TILEMANAGER_H__
#define __TILEMANAGER_H__

#include <vector>
#include "Tile.h"
#include "ComponentManager.h"
#include "TileTypes.h"

const int TILE_SIZE = 64;
const CPoint TILE_OFFSET = CPoint(static_cast<float>(TILE_SIZE) * 0.5f, static_cast<float>(TILE_SIZE) * 0.5f, 0.0, 1.0f);
const int COL_NUM = 60;
const int ROW_NUM = 12;


class TileManager
{
public:
	/* Constructor. */
	TileManager();

	/* Destructor */
	~TileManager() = default;

	static void BuildTileMap();
	static void DrawTileMap();
	static void DebugDrawTileMap();

	TileManager(const TileManager&) = delete; // No copying by mistake.
private:
	static std::vector<Entity> tile_entities;
	static ComponentManager<CTile>& s_tiles;
	static ComponentManager<CPosition>& s_tilePositions; // Manager for all tile positions
	static ComponentManager<CCollider>& s_tileColliders; // Manager for all tile colliders
	static ComponentManager<CEntityRenderer>& s_tileRenderers; // Manager for all tile renderers
};

#endif //!__TILEMANAGER_H__
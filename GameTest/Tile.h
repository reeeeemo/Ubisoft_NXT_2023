#pragma once
#ifndef __TILE_H__
#define __TILE_H__

#include "TileTypes.h"

class CTile
{
public:
	/*
	*  Functions
	*/
	CTile() = default;
	~CTile() = default;

	void SetGridPosition(int inputRow, int inputCol);
	/*
	*  Variables
	*/
	ETileType tile_type;
private:
	// Variables for the grid
	int row;
	int col;
};

#endif __TILE_H__
#include "stdafx.h"

#include "GridPosition.h"
#include "TileManager.h"

CGridPosition::CGridPosition() : row(0.0f), col(0.0f)
{ }

CPoint CGridPosition::GetGridPosition()
{
	return CPoint(col, row, 0.0f, 1.0f);
}

void CGridPosition::SetGridPosition(CPoint destination)
{
	col = Math::AbsValue(destination.x) / TILE_SIZE;
	row = Math::AbsValue(destination.y) / TILE_SIZE;
}

void CGridPosition::SetGridPosition(float x, float y)
{
	col = Math::AbsValue(x) / TILE_SIZE;
	row = Math::AbsValue(y) / TILE_SIZE;
}

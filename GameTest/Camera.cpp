#include "stdafx.h"
#include "Camera.h"
#include "App/app.h"
#include "TileManager.h"

CPoint CCamera::position;



void CCamera::Init()
{
	position = CPoint(0.0, -TILE_SIZE / 2, 0.0, 1.0f);
}

void CCamera::Update()
{
	//position -= TILE_OFFSET;
	position.y = -TILE_SIZE / 2.0f;
	if (position.x < -TILE_SIZE / 2) {
		position.x = -TILE_SIZE / 2;
	}
	else if (position.x > LEVEL_WIDTH - APP_INIT_WINDOW_WIDTH + TILE_SIZE * 7.5f) {
		position.x = LEVEL_WIDTH - APP_INIT_WINDOW_WIDTH + TILE_SIZE * 7.5f;
	}

}

CPoint CCamera::GetPosition()
{
	return position;
}

void CCamera::SetPosition(CPoint pos)
{
	position = pos;
}

CPoint CCamera::DisplaceObject(CPoint objectToDisplace)
{
	return objectToDisplace - position;
}

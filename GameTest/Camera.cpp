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
	//position.x -= APP_INIT_WINDOW_WIDTH / 2;
	/*if (position.x < -TILE_SIZE / 2) {
		position.x = -TILE_SIZE / 2;
	}
	else if (position.x > LEVEL_WIDTH - APP_INIT_WINDOW_WIDTH - TILE_SIZE / 2) {
		position.x = LEVEL_WIDTH - APP_INIT_WINDOW_WIDTH - TILE_SIZE / 2;
	}*/

}

CPoint CCamera::GetPosition()
{
	return position;
}

void CCamera::SetPosition(CPoint pos)
{
	position = pos;
}

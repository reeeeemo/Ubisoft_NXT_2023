#pragma once
#ifndef __ENTITYRENDERER_H__
#define __ENTITYRENDERER_H__

#include "App/app.h"
#include "Point.h"

struct CEntityRenderer
{
	/*
	 *  Functions
	*/
	CEntityRenderer();
	void Render(CPoint sprite_position) const;
	void CreateEntitySprite(const char* file_name, int col, int row);
	void ChangeEntitySprite(const char* file_name, int col, int row, CPoint last_pos);
	void ChangeScale(float scaleValue);
	void Update(float deltaTime, CPoint sprite_position) const;
	void OnDestroy() const;
	/*
	 *	Variables
	 */
	CSimpleSprite* entitySprite = nullptr;
	float spriteWidth;
	float spriteHeight;
};

#endif // !__ENTITYRENDERER_H__
#pragma once
#ifndef __ENTITYRENDERER_H__
#define __ENTITYRENDERER_H__
#include <memory>

#include "App/app.h"
#include "Point.h"

struct CEntityRenderer
{
	/*
	 *  Functions
	*/
	CEntityRenderer();
	void Render() const;
	void CreateEntitySprite(const char* file_name, int col, int row);
	void Update(float deltaTime, CPoint sprite_position) const;
	void OnDestroy() const;
	/*
	 *	Variables
	 */
	CSimpleSprite* entitySprite;
};

#endif // !__ENTITYRENDERER_H__
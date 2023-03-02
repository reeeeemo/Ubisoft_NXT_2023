#pragma once
#ifndef __ENTITYRENDERER_H__
#define __ENTITYRENDERER_H__
#include "App/app.h"

struct CEntityRenderer
{
	/*
	 *  Functions
	*/
	CEntityRenderer();
	void Render();
	void CreateEntitySprite(const char* file_name, int col, int row);
	/*
	 *	Variables
	 */
	CSimpleSprite* entitySprite;
};

#endif // !__ENTITYRENDERER_H__
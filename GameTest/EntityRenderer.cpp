#include "stdafx.h"
#include "EntityRenderer.h"

CEntityRenderer::CEntityRenderer()
{
}

/* Renders sprite previously created. */
void CEntityRenderer::Render()
{
	entitySprite->Draw();
}

/* Creates sprite based on the fileName, columns, and rows given. */
void CEntityRenderer::CreateEntitySprite(const char* file_name, int col, int row)
{
	entitySprite = App::CreateSprite(file_name, col, row);
	if (entitySprite != nullptr)
	{
		entitySprite->SetAngle(0.0f);
		entitySprite->SetScale(1.0f); // Normal sprite size.
	}

}
// entitySprite = App::CreateSprite(".\\Assets\\cow.bmp", 3, 2);
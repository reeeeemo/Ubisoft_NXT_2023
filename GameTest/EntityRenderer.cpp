#include "stdafx.h"
#include "EntityRenderer.h"


CEntityRenderer::CEntityRenderer()
{
}

/* Renders sprite previously created. */
void CEntityRenderer::Render() const
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

/* Updates sprite and position of sprite. */
void CEntityRenderer::Update(float deltaTime, CPoint sprite_position) const
{
	entitySprite->Update(deltaTime);
	entitySprite->SetPosition(sprite_position.x, sprite_position.y);
}

/* When sprite is being destroyed*/
void CEntityRenderer::OnDestroy() const
{
	delete entitySprite;
}

// entitySprite = App::CreateSprite(".\\Assets\\cow.bmp", 3, 2);

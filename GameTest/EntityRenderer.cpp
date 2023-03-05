#include "stdafx.h"
#include "EntityRenderer.h"
#include "Camera.h"
#include "TileManager.h"

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
		spriteWidth = entitySprite->GetWidth();
		spriteHeight = entitySprite->GetHeight();
	}

}

void CEntityRenderer::ChangeEntitySprite(const char* file_name, int col, int row, CPoint last_pos)
{
	// Deleting and re-allocating space.
	delete entitySprite;
	entitySprite = nullptr;

	CreateEntitySprite(file_name, col, row);
	entitySprite->SetPosition(last_pos.x, last_pos.y);
}

void CEntityRenderer::ChangeScale(float scaleValue)
{
	entitySprite->SetScale(scaleValue);
	spriteWidth = entitySprite->GetWidth() * scaleValue;
	spriteHeight = entitySprite->GetHeight() * scaleValue;
}

void CEntityRenderer::ChangeAngle(float degree)
{
	entitySprite->SetAngle(degree);
	spriteWidth = entitySprite->GetWidth();
	spriteHeight = entitySprite->GetHeight();
}

/* Updates sprite and position of sprite. */
void CEntityRenderer::Update(float deltaTime, CPoint sprite_position, bool shouldDisplace) const
{
	entitySprite->Update(deltaTime);
	if (shouldDisplace) {
		entitySprite->SetPosition(CCamera::DisplaceObject(sprite_position).x - (entitySprite->GetWidth() / 2.0), CCamera::DisplaceObject(sprite_position).y - (entitySprite->GetHeight() / 2.0));
	}
	else {
		entitySprite->SetPosition(sprite_position.x, sprite_position.y);
	}
}

/* When sprite is being destroyed*/
void CEntityRenderer::OnDestroy() const
{
	delete entitySprite;
}


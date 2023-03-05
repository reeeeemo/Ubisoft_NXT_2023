#include "stdafx.h"
#include "XBomb.h"
#include "TileManager.h"

// BUGGY, MAKE SURE TO FIX LATER.

/* When we create the object, or respawn it in. */
void CXBomb::OnEnter()
{
	// Variables
	timer = 10.0f;
	radius = 5.0f;

	// Setup the X pattern
	leftCrossRect = CreateEntity();
	rightCrossRect = CreateEntity();

	s_bombRenderers.Create(leftCrossRect);
	s_bombRenderers.Create(rightCrossRect);
	s_bombColliders.Create(leftCrossRect);
	s_bombColliders.Create(rightCrossRect);
	s_bombPositions.Create(leftCrossRect);
	s_bombPositions.Create(rightCrossRect);

	s_bombRenderers.GetComponent(leftCrossRect)->CreateEntitySprite(".\\Assets\\explosion.bmp", 1, 1);
	s_bombRenderers.GetComponent(rightCrossRect)->CreateEntitySprite(".\\Assets\\explosion.bmp", 1, 1);
	s_bombRenderers.GetComponent(leftCrossRect)->ChangeScale(0.7f);
	s_bombRenderers.GetComponent(rightCrossRect)->ChangeScale(0.7f);


	// Initial left cross collider (45 degrees)
	s_bombColliders.GetComponent(leftCrossRect)->UpdateColliderVerticiesWithRadius(s_bombPositions.GetComponent(id)->GetPosition(),
		s_bombRenderers.GetComponent(id)->spriteWidth, s_bombRenderers.GetComponent(id)->spriteHeight, radius, true);
	// Initial right cross collider (45 degrees)
	s_bombColliders.GetComponent(rightCrossRect)->UpdateColliderVerticiesWithRadius(s_bombPositions.GetComponent(id)->GetPosition(),
		s_bombRenderers.GetComponent(id)->spriteWidth, s_bombRenderers.GetComponent(id)->spriteHeight, radius, false);

	CPoint rotation = CPoint(s_bombPositions.GetComponent(id)->x * Math::Cos(45) - s_bombPositions.GetComponent(id)->y * Math::Sin(45),
		s_bombPositions.GetComponent(id)->x * Math::Sin(45) + s_bombPositions.GetComponent(id)->y * Math::Cos(45), 0.0, 1.0f);

	s_bombPositions.GetComponent(leftCrossRect)->SetPosition(CPoint(-rotation.x, -rotation.y, 0.0, 1.0f));
	s_bombPositions.GetComponent(rightCrossRect)->SetPosition(rotation);
}

/* When we are exiting the program. */
void CXBomb::OnExit()
{
}

/* Have the bomb collider check to see if any tiles are touching, if so then BLOW 'EM UP! */
void CXBomb::Execute()
{
	// Look at collisions with the left cross tiles.
	s_bombColliders.GetComponent(leftCrossRect)->UpdateColliderVerticiesWithRadius(s_bombPositions.GetComponent(leftCrossRect)->GetPosition() + TILE_OFFSET,
		s_bombRenderers.GetComponent(leftCrossRect)->spriteWidth, s_bombRenderers.GetComponent(leftCrossRect)->spriteHeight, radius, true);
	TileManager::BreakTileColliding(s_bombColliders.GetComponent(leftCrossRect)->collider);

	// Look at collisions with the right cross tiles.
	s_bombColliders.GetComponent(rightCrossRect)->UpdateColliderVerticiesWithRadius(s_bombPositions.GetComponent(rightCrossRect)->GetPosition() + TILE_OFFSET,
		s_bombRenderers.GetComponent(rightCrossRect)->spriteWidth, s_bombRenderers.GetComponent(rightCrossRect)->spriteHeight, radius, true);
	TileManager::BreakTileColliding(s_bombColliders.GetComponent(rightCrossRect)->collider);
}

/* Renders bomb's explosion via the colliders */
void CXBomb::RenderExplosion()
{
	if (hasExploded) {
		s_bombColliders.GetComponent(leftCrossRect)->DebugDrawCollider();
		s_bombColliders.GetComponent(rightCrossRect)->DebugDrawCollider();
	}
}

void CXBomb::Update()
{
	CPoint rotation = CPoint(s_bombPositions.GetComponent(id)->x * Math::Cos(45) + s_bombPositions.GetComponent(id)->y * Math::Sin(45),
		s_bombPositions.GetComponent(id)->x * Math::Sin(45) - s_bombPositions.GetComponent(id)->y * Math::Cos(45), 0.0, 1.0f);

	s_bombPositions.GetComponent(leftCrossRect)->SetPosition(CPoint(-rotation.x, -rotation.y, 0.0, 1.0f));
	s_bombPositions.GetComponent(rightCrossRect)->SetPosition(rotation);
	s_bombRenderers.GetComponent(leftCrossRect)->ChangeAngle(45.0f);
	s_bombRenderers.GetComponent(rightCrossRect)->ChangeAngle(45.0f);

	s_bombRenderers.GetComponent(leftCrossRect)->entitySprite->SetPosition(s_bombPositions.GetComponent(id)->GetPosition().x, s_bombPositions.GetComponent(id)->GetPosition().y + s_bombRenderers.GetComponent(id)->spriteHeight / 2.0f);
	s_bombRenderers.GetComponent(rightCrossRect)->entitySprite->SetPosition(s_bombPositions.GetComponent(id)->GetPosition().x + s_bombRenderers.GetComponent(id)->spriteWidth / 2.0f, s_bombPositions.GetComponent(id)->GetPosition().y);

	// Look at left cross tiles.
	s_bombColliders.GetComponent(leftCrossRect)->UpdateColliderVerticiesWithRadius(s_bombPositions.GetComponent(leftCrossRect)->GetPosition(),
		s_bombRenderers.GetComponent(leftCrossRect)->spriteWidth, s_bombRenderers.GetComponent(leftCrossRect)->spriteHeight, radius, true);


	// Look at right cross tiles.
	s_bombColliders.GetComponent(rightCrossRect)->UpdateColliderVerticiesWithRadius(s_bombPositions.GetComponent(rightCrossRect)->GetPosition(),
		s_bombRenderers.GetComponent(rightCrossRect)->spriteWidth, s_bombRenderers.GetComponent(rightCrossRect)->spriteHeight, radius, false);
}

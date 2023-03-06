#include "stdafx.h"
#include "ClassicBomb.h"
#include "TileManager.h"
#include "Camera.h"

/* When we create the object, or respawn it in. */
void CClassicBomb::OnEnter()
{
	// Variables
	timer = 20.0f;
	radius = 4.0f;

	// Setup the cross pattern.
	verticalRect = CreateEntity();
	horizontalRect = CreateEntity();

	s_bombRenderers.Create(verticalRect);
	s_bombRenderers.Create(horizontalRect);
	s_bombColliders.Create(verticalRect);
	s_bombColliders.Create(horizontalRect);
	s_bombPositions.Create(verticalRect);
	s_bombPositions.Create(horizontalRect);

	s_bombRenderers.GetComponent(verticalRect)->CreateEntitySprite(".\\Assets\\explosion.bmp", 1, 1);
	s_bombRenderers.GetComponent(horizontalRect)->CreateEntitySprite(".\\Assets\\explosion.bmp", 1, 1);
	s_bombRenderers.GetComponent(verticalRect)->ChangeScale(0.7f);
	s_bombRenderers.GetComponent(horizontalRect)->ChangeScale(0.7f);
	

	// Initial vertical collider
	s_bombColliders.GetComponent(verticalRect)->UpdateColliderVerticiesWithRadius(CCamera::DisplaceObject(CPoint(s_bombPositions.GetComponent(id)->x + s_bombRenderers.GetComponent(id)->spriteWidth / 2,
		s_bombPositions.GetComponent(id)->y + s_bombRenderers.GetComponent(id)->spriteHeight / 2, 0.0, 1.0f)) - TILE_OFFSET,
		s_bombRenderers.GetComponent(id)->spriteWidth, s_bombRenderers.GetComponent(id)->spriteHeight, radius, true);
	// Initial horizontal collider
	s_bombColliders.GetComponent(verticalRect)->UpdateColliderVerticiesWithRadius(CCamera::DisplaceObject(CPoint(s_bombPositions.GetComponent(id)->x + s_bombRenderers.GetComponent(id)->spriteWidth / 2,
		s_bombPositions.GetComponent(id)->y + s_bombRenderers.GetComponent(id)->spriteHeight / 2, 0.0, 1.0f)) - TILE_OFFSET,
		s_bombRenderers.GetComponent(id)->spriteWidth, s_bombRenderers.GetComponent(id)->spriteHeight, radius, false);



	// Initial positions.
	s_bombPositions.GetComponent(verticalRect)->SetPosition(s_bombPositions.GetComponent(id)->GetPosition());
	s_bombPositions.GetComponent(horizontalRect)->SetPosition(s_bombPositions.GetComponent(id)->GetPosition());


}

/* When we are exiting the program. */
void CClassicBomb::OnExit()
{

}

/* Have the bomb collider check to see if any tiles are touching, if so then BLOW 'EM UP! */
void CClassicBomb::Execute()
{
	// Look at collisions with the vertical tiles.
		TileManager::BreakTileColliding(s_bombColliders.GetComponent(verticalRect));
	
	// Look at collision with the middle tile.
		TileManager::BreakTileColliding(s_bombColliders.GetComponent(id));

	// Look at collision with the horizontal tiles.
	TileManager::BreakTileColliding(s_bombColliders.GetComponent(horizontalRect));

}

/* Renders bomb's explosion via the colliders. */
void CClassicBomb::RenderExplosion() {
	if (hasExploded) {
		s_bombColliders.GetComponent(verticalRect)->DebugDrawCollider();
		s_bombColliders.GetComponent(horizontalRect)->DebugDrawCollider();
	}	
}

/* Updates bomb's positions and the other components. */
void CClassicBomb::Update(float deltaTime)
{
	s_bombPositions.GetComponent(verticalRect)->SetPosition(s_bombPositions.GetComponent(id)->GetPosition());
	s_bombPositions.GetComponent(horizontalRect)->SetPosition(s_bombPositions.GetComponent(id)->GetPosition());
	s_bombRenderers.GetComponent(verticalRect)->Update(deltaTime, CCamera::DisplaceObject(CPoint(s_bombPositions.GetComponent(id)->GetPosition().x, s_bombPositions.GetComponent(id)->GetPosition().y + s_bombRenderers.GetComponent(id)->spriteHeight / 2.0f, 0.0, 1.0f)), true);
	s_bombRenderers.GetComponent(horizontalRect)->Update(deltaTime, CCamera::DisplaceObject(CPoint(s_bombPositions.GetComponent(id)->GetPosition().x, s_bombPositions.GetComponent(id)->GetPosition().y + s_bombRenderers.GetComponent(id)->spriteHeight / 2.0f, 0.0, 1.0f)), true);


	//

	// Look at vertical colliders
	s_bombColliders.GetComponent(verticalRect)->UpdateColliderVerticiesWithRadius(CCamera::DisplaceObject(CPoint(s_bombPositions.GetComponent(verticalRect)->x + s_bombRenderers.GetComponent(verticalRect)->spriteWidth / 2,
		s_bombPositions.GetComponent(verticalRect)->y + s_bombRenderers.GetComponent(verticalRect)->spriteHeight / 2, 0.0, 1.0f)) - TILE_OFFSET,
		s_bombRenderers.GetComponent(verticalRect)->spriteWidth, s_bombRenderers.GetComponent(verticalRect)->spriteHeight, radius, true);
	// Look at horizontal colliders
	s_bombColliders.GetComponent(verticalRect)->UpdateColliderVerticiesWithRadius(CCamera::DisplaceObject(CPoint(s_bombPositions.GetComponent(horizontalRect)->x + s_bombRenderers.GetComponent(horizontalRect)->spriteWidth / 2,
		s_bombPositions.GetComponent(horizontalRect)->y + s_bombRenderers.GetComponent(horizontalRect)->spriteHeight / 2, 0.0, 1.0f)) - TILE_OFFSET,
		s_bombRenderers.GetComponent(horizontalRect)->spriteWidth, s_bombRenderers.GetComponent(horizontalRect)->spriteHeight, radius, true);
}

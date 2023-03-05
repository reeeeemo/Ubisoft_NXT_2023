#include "stdafx.h"
#include "XBomb.h"

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


	// Initial vertical collider
	s_bombColliders.GetComponent(leftCrossRect)->UpdateColliderVerticiesWithRadius(s_bombPositions.GetComponent(id)->GetPosition(),
		s_bombRenderers.GetComponent(id)->spriteWidth, s_bombRenderers.GetComponent(id)->spriteHeight, radius, true);
	// Initial horizontal collider
	s_bombColliders.GetComponent(rightCrossRect)->UpdateColliderVerticiesWithRadius(s_bombPositions.GetComponent(id)->GetPosition(),
		s_bombRenderers.GetComponent(id)->spriteWidth, s_bombRenderers.GetComponent(id)->spriteHeight, radius, false);
}

void CXBomb::OnExit()
{
}

void CXBomb::Execute()
{
}

void CXBomb::RenderExplosion()
{
}

void CXBomb::Update()
{
}

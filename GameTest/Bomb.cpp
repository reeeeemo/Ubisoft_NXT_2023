#include "stdafx.h"
#include "Bomb.h"
#include "ClassicBomb.h"
#include "TileManager.h"

std::array<CBomb*, NUM_BOMBS> CBomb::s_bombs;
ComponentManager<CPosition>& CBomb::s_bombPositions = ComponentManager<CPosition>();
ComponentManager<CEntityRenderer>& CBomb::s_bombRenderers = ComponentManager<CEntityRenderer>();
ComponentManager<CRigidbody>& CBomb::s_bombRigidbodies = ComponentManager<CRigidbody>();
ComponentManager<CCollider>& CBomb::s_bombColliders = ComponentManager<CCollider>();


/* Initializing all of the bombs, including their components */
void CBomb::Init()
{
	// Initializing everything
	s_bombs[CLASSIC] = new CClassicBomb;
	for (int i = 0; i < NUM_BOMBS; i++) {
		s_bombs[i]->id = CreateEntity();
		s_bombPositions.Create(s_bombs[i]->id);
		s_bombRenderers.Create(s_bombs[i]->id);
		s_bombRigidbodies.Create(s_bombs[i]->id);
		s_bombColliders.Create(s_bombs[i]->id);

		s_bombs[i]->OnEnter();
	}

	// Adding stats to classic bomb.
	s_bombRenderers.GetComponent(s_bombs[CLASSIC]->id)->CreateEntitySprite(".\\Assets\\classicBomb.bmp", 1, 1);
	s_bombRenderers.GetComponent(s_bombs[CLASSIC]->id)->ChangeScale(0.8f);
	s_bombColliders.GetComponent(s_bombs[CLASSIC]->id)->UpdateColliderVerticies(s_bombPositions.GetComponent(s_bombs[CLASSIC]->id)->GetPosition(),
		s_bombRenderers.GetComponent(s_bombs[CLASSIC]->id)->spriteWidth, s_bombRenderers.GetComponent(s_bombs[CLASSIC]->id)->spriteHeight);


}

/* When player requests to place a bomb */
void CBomb::PlaceBomb(CPoint position, CPoint mousePosition, EBombs bombType, float deltaTime)
{
	if (s_bombs[bombType]->isEnabled) { return; }
	s_bombs[bombType]->OnEnter();
	s_bombPositions.GetComponent(s_bombs[bombType]->id)->SetPosition(position);
	s_bombRigidbodies.GetComponent(s_bombs[bombType]->id)->AddForce((mousePosition - position) / 15.0f, deltaTime);
	s_bombColliders.GetComponent(s_bombs[bombType]->id)->isTrigger = false;
	s_bombs[bombType]->isEnabled = true;
}

/* Basically counts down the timer until bomb explodes. */
void CBomb::UpdateActiveBombs(float deltaTime)
{
	for (int i = 0; i < NUM_BOMBS; i++) {

		if (s_bombs[i]->isEnabled) {
			s_bombs[i]->Update(deltaTime);

			/*if (s_bombRigidbodies.GetComponent(s_bombs[i]->id)->velocity <= CPoint()) {
				if (!s_bombs[i]->stopMoving) {
					CPoint collided_point = TileManager::CheckTileCollidingDistance(s_bombColliders.GetComponent(s_bombs[i]->id));
					s_bombPositions.GetComponent(s_bombs[i]->id)->SetPosition(s_bombPositions.GetComponent(s_bombs[i]->id)->GetPosition() + collided_point);
					s_bombs[i]->stopMoving = true;
				}

			}*/

			// Update the position of the bomb, the renderer, etc.
			if (!s_bombs[i]->stopMoving) {
				s_bombRenderers.GetComponent(s_bombs[i]->id)->Update(deltaTime, s_bombPositions.GetComponent(s_bombs[i]->id)->GetPosition(), true);
				s_bombRigidbodies.GetComponent(s_bombs[i]->id)->Update(deltaTime);
				CPoint new_pos = s_bombRigidbodies.GetComponent(s_bombs[i]->id)->UpdateForce(s_bombPositions.GetComponent(s_bombs[i]->id)->GetPosition(), deltaTime);
				s_bombPositions.GetComponent(s_bombs[i]->id)->SetPosition(new_pos);
			}


			if (!s_bombs[i]->hasExploded) {
				s_bombColliders.GetComponent(s_bombs[CLASSIC]->id)->UpdateColliderVerticies(s_bombPositions.GetComponent(s_bombs[CLASSIC]->id)->GetPosition(),
					s_bombRenderers.GetComponent(s_bombs[CLASSIC]->id)->spriteWidth, s_bombRenderers.GetComponent(s_bombs[CLASSIC]->id)->spriteHeight);
			}


			// Timer
			s_bombs[i]->timer -= 0.1f;
			if (s_bombs[i]->timer <= 0.0f) { // Boom!
				if (s_bombs[i]->hasExploded == true) { // Doing this to let the explosion render.
					s_bombs[i]->isEnabled = false;
					s_bombs[i]->hasExploded = false;
					break;
				}
				s_bombs[i]->hasExploded = true;
				s_bombs[i]->timer = 2.0f; // Little timer so the explosion is visible.
				s_bombs[i]->Execute();
			}
		}
	}
}

/* Renders any active bombs. */
void CBomb::RenderActiveBombs()
{
	for (int i = 0; i < NUM_BOMBS; i++) {
		if (s_bombs[i]->isEnabled) {
			s_bombRenderers.GetComponent(s_bombs[i]->id)->Render();
			s_bombs[i]->RenderExplosion();
		}
	}
}

/* When exiting program. */
void CBomb::Exit()
{
	for (int i = 0; i < NUM_BOMBS; i++) {
		s_bombs[i]->OnExit();

		s_bombPositions.Erase(s_bombs[i]->id);
		s_bombRenderers.Erase(s_bombs[i]->id);
		s_bombColliders.Erase(s_bombs[i]->id);
		if (s_bombRigidbodies.Contains(s_bombs[i]->id)) {
			s_bombRigidbodies.Erase(s_bombs[i]->id);
		}

		s_bombs[i] = nullptr;
	}
}

#include "stdafx.h"
#include "Bomb.h"
#include "ClassicBomb.h"


std::array<CBomb*, NUM_BOMBS> CBomb::s_bombs;
ComponentManager<CPosition>& CBomb::s_bombPositions = ComponentManager<CPosition>();
ComponentManager<CEntityRenderer>& CBomb::s_bombRenderers = ComponentManager<CEntityRenderer>();
ComponentManager<CRigidbody>& CBomb::s_bombRigidbodies = ComponentManager<CRigidbody>();

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

		s_bombs[i]->OnEnter();
	}

	// Adding textures to bombs.
	s_bombRenderers.GetComponent(s_bombs[CLASSIC]->id)->CreateEntitySprite(".\\Assets\\classicBomb.bmp", 1, 1);
}

/* When player requests to place a bomb */
void CBomb::PlaceBomb(CPoint position, CPoint mousePosition, EBombs bombType, float deltaTime)
{
	if (s_bombs[bombType]->isEnabled) { return; }
	s_bombs[bombType]->OnEnter();
	s_bombPositions.GetComponent(s_bombs[bombType]->id)->SetPosition(position);
	s_bombRigidbodies.GetComponent(s_bombs[bombType]->id)->AddForce((mousePosition - position) / 15.0f, deltaTime);
	s_bombs[bombType]->isEnabled = true;
}

/* Basically counts down the timer until bomb explodes. */
void CBomb::UpdateActiveBombs(float deltaTime)
{
	for (int i = 0; i < NUM_BOMBS; i++) {

		if (s_bombs[i]->isEnabled) {
			s_bombRenderers.GetComponent(s_bombs[i]->id)->Update(deltaTime, s_bombPositions.GetComponent(s_bombs[i]->id)->GetPosition());
			s_bombRigidbodies.GetComponent(s_bombs[i]->id)->Update(deltaTime);
			CPoint new_pos = s_bombRigidbodies.GetComponent(s_bombs[i]->id)->UpdateForce(s_bombPositions.GetComponent(s_bombs[i]->id)->GetPosition(), deltaTime);
			s_bombPositions.GetComponent(s_bombs[i]->id)->SetPosition(new_pos);
			s_bombs[i]->timer -= 0.1f;
			if (s_bombs[i]->timer <= 0.0f) { // Boom!
				s_bombs[i]->Execute();
				s_bombs[i]->isEnabled = false;
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

		s_bombs[i] = nullptr;
	}
}

#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

#include <array>
#include <memory>
#include "app/app.h"
#include "Point.h"
#include "ComponentManager.h"
#include "Button.h"
#include "TileManager.h"

enum EScenes
{
	MAIN_MENU,
	MAIN,
	END,
	NUM_SCENES
};


class CScene
{
public:
	CScene();
	virtual ~CScene();

	// Scene Lifecycle functions.
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents(float deltaTime) = 0;

	// Static functions
	static void Init();
	static void UpdateCurrentScene(float deltaTime);
	static void RenderCurrentScene();

	static void Exit();

	static void ChangeScenes(EScenes scene);
protected:
	// Scene Functions
	virtual void OnEnter();
	virtual void OnExit();

	// Scene variables


	static std::array<CScene*, NUM_SCENES> s_scenes;

	static CScene* s_current_scene;

	// Game-Specific Variables
	static std::vector<Entity> s_entities; // All of the entities in the scene
	static ComponentManager<CPosition>& s_positions; // Manager for all positions
	static ComponentManager<CEntityRenderer>& s_renderers; // Manager for all entity renderers
	static ComponentManager<CRigidbody>& s_rigidbodies; // Manager for all entity rigidbodies (physics)
	static ComponentManager<CCollider>& s_colliders; // Manager for all entity colliders
	static const Entity player; // Player entity.

};

#endif // !__SCENE_H__


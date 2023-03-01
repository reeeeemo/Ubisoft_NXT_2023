#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

#include <array>
#include "app/app.h"
#include "Point.h"
#include "ComponentManager.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

	// Scene Lifecycle functions.
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void HandleEvents() = 0;

	static void Init();
	static void UpdateCurrentScene();
	static void RenderCurrentScene();

	static void Exit();
protected:
	// Scene Functions
	virtual void OnEnter();
	virtual void OnExit();

	// Scene variables
	enum EScenes
	{
		MAIN_MENU,
		MAIN,
		END,
		NUM_SCENES
	};

	static std::array<CScene*, NUM_SCENES> s_scenes;

	static CScene* s_current_scene;

	// Game-Specific Variables
	static std::vector<Entity> s_entities; // All of the entities in the scene
	static ComponentManager<CPosition>& s_positions; // Manager for all positions
	static const Entity player; // Player entity.

};

#endif // !__SCENE_H__


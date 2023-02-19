#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

#include <array>

class CScene
{
public:
	CScene();

	// Scene Lifecycle functions.
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void HandleEvents() = 0;

	static void Init();
	static void UpdateCurrentScene();
	static void RenderCurrentScene();

	static void Exit();
protected: // proyected
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;


	enum EScenes
	{
		MAIN_MENU,
		MAIN,
		END,
		NUM_SCENES
	};

	std::array<EScenes*, NUM_SCENES> s_scenes;

	static CScene* current_scene;
};

#endif // !__SCENE_H__


#pragma once
#ifndef __MENUSCREEN_H__
#define __MENUSCREEN_H__

#include "Scene.h"

class CMenuScene : public CScene
{
public:
	CMenuScene() = default;

	void Update(float deltaTime) override;
	void Render() override;
	void HandleEvents() override;
private:
	void OnEnter() override;
	void OnExit() override;

	// Testing Variables
};

#endif // !__MENUSCREEN_H__
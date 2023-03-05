#pragma once

#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__

#include "Scene.h"

class CMainScene : public CScene
{
public:
	CMainScene() = default;

	void Update(float deltaTime) override;
	void Render() override;
	void HandleEvents(float deltaTime) override;
private:
	/*
	*  Functions
	*/
	void OnEnter() override;
	void OnExit() override;
	/*
	*  Variables
	*/
	CPoint plrSpeed = CPoint();
	EBombs current_bomb = EBombs::CLASSIC;
};

#endif // !__MAINSCENE_H__


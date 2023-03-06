#pragma once

#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__

#include "Scene.h"

const int NEXT_ENEMY_TIME = 25.0f;

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
	float timerUntilNextEnemy = 0;
};

#endif // !__MAINSCENE_H__


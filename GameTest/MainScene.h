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
	void OnEnter() override;
	void OnExit() override;
};

#endif // !__MAINSCENE_H__


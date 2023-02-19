#pragma once
#include "Scene.h"
#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__

class CMainScene : public CScene
{
public:
	CMainScene() = default;

	void Update() override;
	void Render() override;
	void HandleEvents() override;
private:
	void OnEnter() override;
	//std::array<>
};

#endif // !__MAINSCENE_H__


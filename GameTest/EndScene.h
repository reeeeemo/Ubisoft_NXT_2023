#pragma once
#include "Scene.h"
#ifndef __ENDSCENE_h__
#define __ENDSCENE_H__

class CEndScene : public CScene
{
public:
	CEndScene() = default;

	void Update() override;
	void Render() override;
	void HandleEvents() override;
private:
	void OnEnter() override;
};

#endif // !__ENDSCENE_H__
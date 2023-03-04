//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
//------------------------------------------------------------------------
#include "Math.h"
#include "app/app.h"
#include "Scene.h"
#include "Button.h"
#include "Bomb.h"
//------------------------------------------------------------------------
// Example data....
//------------------------------------------------------------------------
//CSimpleSprite *testSprite;
//enum
//{
//	ANIM_FORWARDS,
//	ANIM_BACKWARDS,
//	ANIM_LEFT,
//	ANIM_RIGHT,
//};
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	CBomb::Init();
	CButton::Init();
	CScene::Init();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	CButton::Update(deltaTime);
	CScene::UpdateCurrentScene(deltaTime);
	CBomb::UpdateActiveBombs(deltaTime);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	CButton::Render();
	CScene::RenderCurrentScene();
	CBomb::RenderActiveBombs();

}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	CBomb::Exit();
	CButton::Exit();
	CScene::Exit();
}
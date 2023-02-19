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
	CScene::Init();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	CScene::UpdateCurrentScene();
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	CScene::RenderCurrentScene();
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	CScene::Exit();
}
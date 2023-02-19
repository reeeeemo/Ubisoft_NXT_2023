#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
{

}

void CScene::Init()
{
	//s_scenes[MAIN_MENU] = new CMenuScene;
	//s_scenes[MAIN] = new CMainScene;
	//s_scenes[END] = new CEndScene;
	//current_scene = s_scenes[MAIN_MENU];
	current_scene->OnEnter();
}

void CScene::UpdateCurrentScene()
{
	current_scene->Update();
}

void CScene::RenderCurrentScene()
{
	current_scene->Render();
}

void CScene::Exit()
{

}

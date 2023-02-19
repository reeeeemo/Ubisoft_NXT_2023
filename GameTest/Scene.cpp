#include "stdafx.h"
#include "Scene.h"

#include "MenuScene.h"
#include "MainScene.h"
#include "EndScene.h"

std::array<CScene*, CScene::NUM_SCENES> CScene::s_scenes;

CScene* CScene::s_current_scene = nullptr;	

CScene::CScene() = default;

CScene::~CScene() = default;

void CScene::Init()
{
	s_scenes[MAIN_MENU] = new CMenuScene;
	s_scenes[MAIN] = new CMainScene;
	s_scenes[END] = new CEndScene;

	s_current_scene = s_scenes[MAIN_MENU];
	s_current_scene->OnEnter();
}

void CScene::UpdateCurrentScene()
{
	s_current_scene->Update();
}

void CScene::RenderCurrentScene()
{
	s_current_scene->Render();
}

void CScene::Exit()
{
	// Clearing up memory before exit of program!
	for (uint32_t i = 0; i < CScene::NUM_SCENES; i++)
	{
		delete s_scenes[i];
	}
}

void CScene::OnEnter()
{
}

void CScene::OnExit()
{
}



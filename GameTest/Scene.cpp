#include "stdafx.h"
#include "Scene.h"

#include "MenuScene.h"
#include "MainScene.h"
#include "EndScene.h"

// Static initializations.
std::array<CScene*, CScene::NUM_SCENES> CScene::s_scenes;

CScene* CScene::s_current_scene = nullptr;	

CScene::CScene() = default;

CScene::~CScene() = default;

std::vector<Entity> CScene::s_entities; // All of the entities in the scene
ComponentManager<CPosition>& CScene::s_positions = ComponentManager<CPosition>(); // Position manager for all entities!
ComponentManager<CEntityRenderer>& CScene::s_renderers = ComponentManager<CEntityRenderer>(); // Manager for all entity renderers.
ComponentManager<CRigidbody>& CScene::s_rigidbodies = ComponentManager<CRigidbody>(); // Manager for all entity rigidbodies (physics)
const Entity CScene::player = CreateEntity();

void CScene::Init()
{
	s_scenes[MAIN_MENU] = new CMenuScene;
	s_scenes[MAIN] = new CMainScene;
	s_scenes[END] = new CEndScene;

	s_current_scene = s_scenes[MAIN_MENU];
	s_current_scene->OnEnter();
}

void CScene::UpdateCurrentScene(float deltaTime)
{
	s_current_scene->Update(deltaTime);
	s_current_scene->HandleEvents(deltaTime);
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
		s_scenes[i] = nullptr;
	}
	s_current_scene = nullptr;

}

void CScene::OnEnter()
{
}

void CScene::OnExit()
{
	
}



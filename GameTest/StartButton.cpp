#include "stdafx.h"
#include "StartButton.h"
#include "Scene.h"

void CStartButton::OnEnter()
{

}

void CStartButton::OnExit()
{
}

void CStartButton::Execute()
{
	CButton::DisableButton(START);
	CScene::ChangeScenes(MAIN);
}

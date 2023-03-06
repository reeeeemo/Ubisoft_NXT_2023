#include "stdafx.h"
#include "EndScene.h"

void CEndScene::Update(float deltaTime)
{
}

void CEndScene::Render()
{
	if (CScore::playerWon) {
		App::Print(600, 300, "You win!");
	}
	else {
		App::Print(600, 300, "You lost...");
	}
	CScore::RenderScore();
}

void CEndScene::HandleEvents(float deltaTime)
{
}

void CEndScene::OnEnter()
{
}

void CEndScene::OnExit() {
	CScore::SetRenderFinalScore(false);
}
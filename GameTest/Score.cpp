#include "stdafx.h"
#include "Score.h"
#include "App/app.h"

// Static variable initializers
int CScore::score;
int CScore::obstaclesDestroyed;
std::string CScore::m_score;
std::string CScore::m_obstaclesDestroyed;
bool CScore::renderFinalScore = false;
bool CScore::playerWon = false;

/* When we are getting into the scene. */
void CScore::Init()
{
	score = 0;
	obstaclesDestroyed = 0;

	m_obstaclesDestroyed = "Obstacles Destroyed: " + std::to_string(0);
	m_score = "Score: " + std::to_string(0);
}

/* Renders all of the score and destruction text. */
void CScore::RenderScore()
{
	if (renderFinalScore) {
		App::Print(300, 300, m_score.c_str());
		App::Print(300, 250, m_obstaclesDestroyed.c_str());
	}
	else {
		App::Print(800, 700, m_score.c_str());
		App::Print(800, 725, m_obstaclesDestroyed.c_str());
	}
}

/* When we are leaving the scene. */
void CScore::Exit()
{
}

void CScore::UpdateObstaclesDestroyed()
{
	obstaclesDestroyed++;
	m_obstaclesDestroyed = "Obstacles Destroyed: " + std::to_string(obstaclesDestroyed);
	UpdateScore(obstaclesDestroyed * 1.5f);
}


int CScore::GetObstaclesDestroyed()
{
	return obstaclesDestroyed;
}

void CScore::UpdateScore(int amount)
{
	score += amount;
	m_score = "Score: " + std::to_string(score);
}

void CScore::SetRenderFinalScore(bool doRender)
{
	renderFinalScore = doRender;
}


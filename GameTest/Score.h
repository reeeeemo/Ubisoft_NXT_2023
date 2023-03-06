#pragma once
#ifndef __SCORE_H__
#define __SCORE_H__

#include <string>

class CScore
{
public:
	
	/* Scene lifecycle functions. */
	static void Init();
	static void RenderScore();
	static void Exit();



	static void UpdateObstaclesDestroyed();
	static int GetObstaclesDestroyed();
	static void UpdateScore(int amount);
	static void SetRenderFinalScore(bool doRender);
	static bool playerWon;
private:
	static int score;
	static int obstaclesDestroyed;
	static std::string m_score;
	static std::string m_obstaclesDestroyed;
	static bool renderFinalScore;
};

#endif //!__SCORE_H__
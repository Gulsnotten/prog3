#pragma once
#include <vector>
#include "Score.h"

class Highscores
{
private:
	std::vector<Score*> m_scores;

	void CreateEmptyScores();
	void UpdateScores();
public:
	Highscores();
	~Highscores();

	std::vector<Score*> GetScores();
	Score* GetHighscore();

	bool TryScore(int p_score);
	bool AddScore(Score* p_score);
};
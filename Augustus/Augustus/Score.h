#pragma once
#include <string>

struct Score
{
	// in case I want to implement names etc.

	int m_score;

	Score();
	Score(int p_score);
	Score(std::string p_string);

	std::string ToFileString();
};
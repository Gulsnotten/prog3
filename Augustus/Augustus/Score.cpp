#include "stdafx.h"
#include "Score.h"

Score::Score()
{
}

Score::Score(int p_score)
	: m_score(p_score)
{
}

Score::Score(std::string p_string)
{
	std::string str = p_string;

	// delete all instances of '\n'
	for (unsigned int i = 0; i < str.size(); i++) {
		if (str[i] == '\n') {
			str.erase(str.begin() + i);
			i--;
		}
	}

	// if add more members, chop the string into smaller strings with ; as divider

	m_score = atoi(str.c_str());
}

std::string Score::ToFileString()
{
	return std::to_string(m_score);
}

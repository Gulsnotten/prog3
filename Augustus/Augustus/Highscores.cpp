#include "stdafx.h"
#include "Highscores.h"

#include "TextLoader.h"
 

void Highscores::CreateEmptyScores()
{
	m_scores.clear();

	for (int i = 0; i < Config::MAX_SCORES; i++) {
		m_scores.push_back(new Score(Config::START_SCORE - i));
	}

	UpdateScores();
}

void Highscores::UpdateScores()
{
	std::vector<std::string> data;
	
	for (auto s : m_scores) {
		data.push_back(s->ToFileString());
	}

	TextFileManipulator::WriteFile(Config::SCORE_PATH, data);
}

Highscores::Highscores()
{
	std::string file = Config::SCORE_PATH;
	if (TextFileManipulator::FileExists(file)) {
		m_scores.clear();
		for (auto s : TextFileManipulator::LoadFile(Config::SCORE_PATH)) {
			
			m_scores.push_back(new Score(s));
		}
	}
	else {
		CreateEmptyScores();
	}
}

Highscores::~Highscores()
{
	for (auto s : m_scores) {
		delete s;
		s = nullptr;
	}
}

std::vector<Score*> Highscores::GetScores()
{
	return m_scores;
}

Score * Highscores::GetHighscore()
{
	return m_scores[0];
}

bool Highscores::TryScore(int p_score)
{
	bool add = false;
	for (auto s : m_scores) {
		if (p_score > s->m_score) {
			add = true;
		}
	}
	return add;
}

bool Highscores::AddScore(Score * p_score)
{
	// this shouldn't happen! use "TryScore" first
	// this function will delete the pointer if it can't be added
	if (!TryScore(p_score->m_score)) {
		delete p_score;
		return false;
	}

	for (unsigned int i = 0; i < m_scores.size(); i++) {
		if (p_score->m_score > m_scores[i]->m_score) { // add here

			m_scores.insert(m_scores.begin() + i, p_score);
			m_scores.pop_back(); // delete the bottom score
			UpdateScores();

			return true;
		}
	}

	return false;
}
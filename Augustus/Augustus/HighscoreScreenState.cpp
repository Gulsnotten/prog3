#include "stdafx.h"
#include "HighscoreScreenState.h"

#include "ServiceLocator.h"
#include "Highscores.h"
#include "InputManager.h"
#include "Font.h"
#include "vect2.h"
#include "Config.h"
#include "BlinkModule.h"

HighscoreScreenState::HighscoreScreenState(int p_score)
{
	m_score = p_score;

	m_highscoreswPtr = ServiceLocator<Highscores>::GetService();
	m_input = ServiceLocator<InputManager>::GetService();
	m_fontwPtr = ServiceLocator<Font>::GetService();
	m_blinker = new BlinkModule(Config::TEXT_FLASH_SPEED);

	m_yellow = SDL_Color();
	m_yellow.r = 255;
	m_yellow.g = 255;
	m_yellow.b = 0;
	m_yellow.a = 255;
}

HighscoreScreenState::~HighscoreScreenState()
{
	delete m_blinker;
	m_blinker = nullptr;
}

void HighscoreScreenState::Enter()
{
}

void HighscoreScreenState::Exit()
{
}

PDA::PDA_ReturnFlag HighscoreScreenState::Update(float p_delta)
{
	m_blinker->Update(p_delta);

	if (m_input->IsKeyDownOnce(SDL_SCANCODE_SPACE)) {
		return PDA::PDA_ReturnFlag::Pop;
	}

	return PDA::PDA_ReturnFlag::Keep;
}

void HighscoreScreenState::Draw()
{
	float center = Config::WINDOW_WIDTH / 2;

	m_fontwPtr->DrawCentered(Vect2(center, Config::TILE_SIZE * 8), "HIGH SCORES");

	int y = 12;
	Vect2 pos;
	std::string str;
	for (auto s : m_highscoreswPtr->GetScores()) {
		pos = Vect2(center + Config::TILE_SIZE * 2.5f, Config::TILE_SIZE * y);
		str = std::to_string(s->m_score) + "0";

		if (s->m_score == m_score) {
			if (m_blinker->IsShowing()) {
				m_fontwPtr->DrawLeftAnchor(pos, str, m_yellow);
			}
		}
		else {
			m_fontwPtr->DrawLeftAnchor(pos, str);
		}

		y += 2;
	}

	pos = Vect2(center, Config::WINDOW_HEIGHT - Config::TILE_SIZE * 8);
	m_fontwPtr->DrawCentered(pos, "PRESS SPACE");
}

IState_PDA * HighscoreScreenState::NextState()
{
	return nullptr;
}

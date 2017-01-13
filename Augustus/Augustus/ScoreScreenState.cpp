#include "stdafx.h"
#include "ScoreScreenState.h"

#include "ServiceLocator.h"
#include "BlinkModule.h"
 
#include "SoundManager.h"
#include "InputManager.h"
#include "Highscores.h"

ScoreScreenState::ScoreScreenState(GameStateData* p_data)
	: IGameState(p_data)
{
	m_highscoreswPtr = ServiceLocator<Highscores>::GetService();
	m_input = ServiceLocator<InputManager>::GetService();
	m_blinker = new BlinkModule(Config::TEXT_FLASH_SPEED);

	m_yellow = SDL_Color();
	m_yellow.r = 255;
	m_yellow.g = 255;
	m_yellow.b = 0;
	m_yellow.a = 255;

	std::string file = "../Assets/sound/the_pac_is_back_short.wav";
	SoundManager* soundManager = ServiceLocator<SoundManager>::GetService();
	m_musicwPtr = soundManager->CreateMusic(file);
}

ScoreScreenState::~ScoreScreenState()
{
	delete m_blinker;
	m_blinker = nullptr;
}

bool ScoreScreenState::Update(float p_delta)
{
	m_blinker->Update(p_delta);

	if (m_input->IsKeyDownOnce(SDL_SCANCODE_SPACE)) {
		return false;
	}

	return true;
}

void ScoreScreenState::Draw()
{
	float center = Config::WINDOW_WIDTH / 2;

	m_datawPtr->m_fontwPtr->DrawCentered(Vect2(center, Config::TILE_SIZE * 8), "HIGH SCORES");

	int y = 12;
	Vect2 pos;
	std::string str;
	for (auto s : m_highscoreswPtr->GetScores()) {
		pos = Vect2(float(center + Config::TILE_SIZE * 2.5f), float(Config::TILE_SIZE * y));
		str = std::to_string(s->m_score) + "0";

		if (s->m_score == m_datawPtr->GetScore()) {
			if (m_blinker->IsShowing()) {
				m_datawPtr->m_fontwPtr->DrawLeftAnchor(pos, str, m_yellow);

				if (m_datawPtr->GotHighscore()) {
					pos = Vect2(center, Config::WINDOW_HEIGHT - Config::TILE_SIZE * 12);
					m_datawPtr->m_fontwPtr->DrawCentered(pos, "NEW HIGHSCORE!", m_yellow);
				}
			}
		}
		else {
			m_datawPtr->m_fontwPtr->DrawLeftAnchor(pos, str);
		}

		y += 2;
	}

	pos = Vect2(center, Config::WINDOW_HEIGHT - Config::TILE_SIZE * 8);
	m_datawPtr->m_fontwPtr->DrawCentered(pos, "PRESS SPACE");
}

void ScoreScreenState::Enter()
{
	if (m_datawPtr->GotHighscore()) {
		m_musicwPtr->Play();
	}
}

void ScoreScreenState::Exit()
{
	m_musicwPtr->Stop();
}

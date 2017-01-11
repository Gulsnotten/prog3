#include "stdafx.h"
#include "GameSession.h"

#include "IGameState.h"
#include "PlayingState.h"
#include "GameStateData.h"
#include "StartAnimationState.h"
#include "DeathAnimationState.h"
#include "WinAnimationState.h"

#include "HighscoreScreenState.h"

#include "Config.h"

void GameSession::SwitchState(IGameState * p_state)
{
	if (m_currentStatewPtr != nullptr)
		m_currentStatewPtr->Exit();
	m_currentStatewPtr = p_state;
	m_currentStatewPtr->Enter();
}

GameSession::GameSession()
{
	m_data = new GameStateData();

	m_data->StartGame(Config::START_EXTRA_LIFE);

	m_playing = new PlayingState(m_data);
	m_startAnimation = new StartAnimationState(m_data);
	m_deathAnimation = new DeathAnimationState(m_data);
	m_winAnimation = new WinAnimationState(m_data);
	SwitchState(m_startAnimation);
}


GameSession::~GameSession()
{
	m_currentStatewPtr->Exit();

	m_data->Exit();

	delete m_data;
	m_data = nullptr;

	delete m_playing;
	m_playing = nullptr;
}

void GameSession::Enter()
{
}

void GameSession::Exit()
{
	m_currentStatewPtr->Exit();
}


PDA::PDA_ReturnFlag GameSession::Update(float p_delta)
{
	bool ret = m_currentStatewPtr->Update(p_delta);
	m_data->Update(p_delta);

	if (!ret) {
		if (m_currentStatewPtr == m_startAnimation) {
			SwitchState(m_playing);
		}
		else if (m_currentStatewPtr == m_playing) {
			if (m_data->m_player->IsDead()) {	// LOSE
				SwitchState(m_deathAnimation);
			}
			else {								// WIN
				SwitchState(m_winAnimation);
			}
		}
		else if (m_currentStatewPtr == m_deathAnimation) {
			if (!m_data->IsGameOver()) {
				m_data->Retry();
				SwitchState(m_startAnimation);
			}
			else {
				m_data->CheckAgainstHighscores();

				return PDA::PDA_ReturnFlag::Switch;
			}
		}
		else if (m_currentStatewPtr == m_winAnimation) {
			m_data->NextScreen();
			SwitchState(m_startAnimation);
		}
	}

	return PDA::PDA_ReturnFlag::Keep;
}

void GameSession::Draw()
{
	m_currentStatewPtr->Draw();
}

IState_PDA * GameSession::NextState()
{
	return new HighscoreScreenState(m_data->GetScore());
}
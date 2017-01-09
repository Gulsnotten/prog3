#include "stdafx.h"
#include "PlayingState.h"

#include "Config.h"
#include "GhostSoundPicker.h"
#include "Level.h"

void PlayingState::CheckCollision()
{
	for (auto g : m_datawPtr->m_ghosts) {
		if (g->GetPos()->Round() == m_datawPtr->m_player->GetPos()->Round()) {
			if (g->IsFleeing()) {
				g->RunToHouse();
				m_pause.SetPause(Config::PAUSE_TIME);
				m_datawPtr->m_player->StopSound();
			}
			else if (!g->IsDead()) {
				Lose();
			}
		}
	}
}

void PlayingState::Win()
{
	m_pause.SetPause(Config::WIN_PAUSE_TIME);
	m_ghostSound->StopSongs();
	m_datawPtr->m_player->StopSound();
}

void PlayingState::Lose()
{
	m_datawPtr->m_player->Kill();
	m_ghostSound->StopSongs();
	m_pause.SetPause(Config::PAUSE_TIME);
}

PlayingState::PlayingState(GameStateData * p_data)
	: IGameState(p_data)
{
}

PlayingState::~PlayingState()
{
	delete m_ghostSound;
	m_ghostSound = nullptr;
}

bool PlayingState::Update(float p_delta)
{
	int oldPelletsCount = 0;

	if (!m_pause.Update(p_delta)) {
		oldPelletsCount = m_datawPtr->m_level->PelletsCount();

		for (auto g : m_datawPtr->m_ghosts)
			g->Update(p_delta);
		m_datawPtr->m_player->Update(p_delta);

		m_ghostSound->PickSong();

		CheckCollision();
	}

	if (!m_pause.IsPaused()) {
		if (m_datawPtr->m_player->IsDead())
			return false;
		if (m_datawPtr->m_level->PelletsCount() == 0) {
			if (oldPelletsCount > 0) {
				Win();
			}
			else {
				return false;
			}
		}
	}

	return true;
}

void PlayingState::Draw()
{
	m_datawPtr->DrawAll();
}

void PlayingState::Enter()
{
	m_ghostSound = new GhostSoundPicker(m_datawPtr->m_ghosts);
	m_datawPtr->m_player->AddObserver(this);
}

void PlayingState::Exit()
{
	m_ghostSound->StopSongs();
	m_datawPtr->m_player->StopSound();
}

void PlayingState::Notify(std::string p_msg)
{
	if (p_msg == Config::POWER_UP_MSG) {
		for (auto g : m_datawPtr->m_ghosts) {
			g->Flee();
		}
	}
}

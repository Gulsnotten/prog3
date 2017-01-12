#include "stdafx.h"
#include "PlayingState.h"

#include "Config.h"
#include "GhostSoundPicker.h"
#include "Level.h"

#include "CollisionManager.h"

#include "Animation.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "ServiceLocator.h"

bool PlayingState::CheckGhostCollision()
{
	for (auto g : m_datawPtr->m_ghosts) {
		if (CollisionManager::CheckCollision(g, m_datawPtr->m_player)) {
			if (!g->IsFleeing() && !g->IsDead()) {
				Lose();
			}

			if (g->IsFleeing()) {
				m_pause.SetPause(Config::PAUSE_TIME);

				m_combo++;
				int multiplier = m_combo * m_combo;
				Animation* score = nullptr;
				if (m_datawPtr->AddPoints(multiplier * Config::POINT_GHOST)) {
					score = m_1UPAnimation;
				}
				else {
					score = m_scoreAnimations[m_combo - 1];
					m_eatGhostSoundwPtr->Play();
				}
				g->RunToHouse(score);

				return true; // only one ghost may flee per frame
			}
		}
	}

	return false;
}

PlayingState::Food PlayingState::CheckFoodCollision()
{
	bool ate_pellet = false;
	bool ate_power_up = false;

	if (m_datawPtr->m_level->PelletCollision(m_datawPtr->m_player)) {
		ate_pellet = true;
	}
	if (m_datawPtr->m_level->PowerUpCollision(m_datawPtr->m_player)) {
		ate_power_up = true;
	}

	if (ate_pellet) {
		AtePellet();
	}
	if (ate_power_up) {
		AtePowerup();
	}

	if (ate_power_up)
		return PowerUpFood;
	if (ate_pellet)
		return PelletFood;
	return NothingFood;
}

void PlayingState::Win()
{
	m_hasWon = true;
	m_pause.SetPause(Config::WIN_PAUSE_TIME);
	m_ghostSound->StopSongs();
}

void PlayingState::Lose()
{
	if (!m_datawPtr->m_player->IsDead()) {
		m_datawPtr->m_player->Kill();
		m_ghostSound->StopSongs();
		m_pause.SetPause(Config::PAUSE_TIME);
	}
}

void PlayingState::AtePellet()
{
	m_datawPtr->AddPoints(Config::POINT_PELLET);

	CheckIfWin();
}

void PlayingState::AtePowerup()
{
	m_combo = 0;
	for (auto g : m_datawPtr->m_ghosts) {
		g->Flee();
		m_datawPtr->AddPoints(Config::POINT_POWER_UP);
	}

	CheckIfWin();
}

void PlayingState::CheckIfWin()
{
	if (m_datawPtr->m_level->PelletsCount() == 0) {
		Win();
	}
}

PlayingState::PlayingState(GameStateData * p_data)
	: IGameState(p_data)
{
	m_wakaSwitch = false;

	SpriteManager* spriteManager = ServiceLocator<SpriteManager>::GetService();
	std::string score_file = "../Assets/ghost_score.png";

	m_scoreAnimations.clear();
	for (int x = 0; x < 4; x++) {
		AnimationFrame next_frame = AnimationFrame(
			spriteManager->CreateSprite(score_file, x * 16, 0, 16, 16),
			1000
		);
		Animation* next_animation = new Animation();
		next_animation->AddFrame(next_frame);
		m_scoreAnimations.push_back(next_animation);
	}


	m_1UPAnimation = new Animation();
	AnimationFrame next_frame = AnimationFrame(
		spriteManager->CreateSprite(score_file, 64, 0, 22, 16),
		1000
	);
	m_1UPAnimation->AddFrame(next_frame);


	SoundManager* soundManager = ServiceLocator<SoundManager>::GetService();
	m_eatGhostSoundwPtr = soundManager->CreateSound("../Assets/sound/eatghost.wav");
	m_wakaSoundwPtr = soundManager->CreateSound("../Assets/sound/waka.wav");
}

PlayingState::~PlayingState()
{
	delete m_ghostSound;
	m_ghostSound = nullptr;

	for (auto s : m_scoreAnimations) {
		delete s;
	}

	delete m_1UPAnimation;
}

bool PlayingState::Update(float p_delta)
{
	if (!m_pause.Update(p_delta)) {
		for (auto g : m_datawPtr->m_ghosts)
			g->Update(p_delta);


		bool bumped = m_datawPtr->m_player->Update(p_delta);
		Food food = CheckFoodCollision();
		CheckGhostCollision();

		if (m_datawPtr->m_player->IsDead()) {
			m_ghostSound->StopSongs();
		}
		else {
			m_ghostSound->PickSong();
		}

		if (food == PowerUpFood || food == PelletFood) {
			if (m_wakaSwitch == false) {
				m_wakaSoundwPtr->Play();
			}
			m_wakaSwitch = !m_wakaSwitch;
		}
	}
	else if (!m_hasWon){
		for (auto g : m_datawPtr->m_ghosts) { // update the dead ghosts
			if (g->HasStartedRunning())
				g->Update(p_delta);
		}
	}

	m_datawPtr->m_level->Update(p_delta); // update the pellet animation regardless

	if (!m_pause.IsPaused()) {
		if (m_datawPtr->m_player->IsDead()) {
			return false;
		}
		if (m_hasWon) {
			return false;
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
	m_hasWon = false;
	m_ghostSound = new GhostSoundPicker(m_datawPtr->m_ghosts);
}

void PlayingState::Exit()
{
	m_ghostSound->StopSongs();
}
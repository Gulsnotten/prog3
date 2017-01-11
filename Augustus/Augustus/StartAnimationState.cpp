#include "stdafx.h"
#include "StartAnimationState.h"

#include "ServiceLocator.h"
#include "SoundManager.h"
#include "DrawManager.h"
#include "Font.h"
#include "Config.h"
#include "Level.h"

StartAnimationState::StartAnimationState(GameStateData * p_data)
	: IGameState(p_data)
{
	SoundManager* soundManager = ServiceLocator<SoundManager>::GetService();
	m_musicwPtr = soundManager->CreateMusic("../Assets/sound/beginning.wav");
	m_drawManagerwPtr = ServiceLocator<DrawManager>::GetService();

	m_yellow = SDL_Color();
	m_yellow.r = 255;
	m_yellow.g = 255;
	m_yellow.b = 0;
	m_yellow.a = 255;
}

StartAnimationState::~StartAnimationState()
{
}

bool StartAnimationState::Update(float p_delta)
{
	return m_musicwPtr->IsPlaying();
}

void StartAnimationState::Draw()
{
	m_datawPtr->DrawAll();

	Vect2 pos = Vect2(Config::WINDOW_WIDTH / 2 + Config::TILE_SIZE / 2, 20 * Config::TILE_SIZE);

	m_datawPtr->m_fontwPtr->DrawCentered(pos, "READY!", m_yellow);
}

void StartAnimationState::Enter()
{
	m_musicwPtr->Play();
	m_datawPtr->m_level->ResetAnimation();
}

void StartAnimationState::Exit()
{
}

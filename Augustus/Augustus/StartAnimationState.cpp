#include "stdafx.h"
#include "StartAnimationState.h"

#include "ServiceLocator.h"
#include "SoundManager.h"

StartAnimationState::StartAnimationState(GameStateData * p_data)
	: IGameState(p_data)
{
	SoundManager* soundManager = ServiceLocator<SoundManager>::GetService();
	m_musicwPtr = soundManager->CreateMusic("../Assets/sound/beginning.wav");
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
}

void StartAnimationState::Enter()
{
	m_musicwPtr->Play();
}

void StartAnimationState::Exit()
{
}

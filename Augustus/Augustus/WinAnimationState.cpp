#include "stdafx.h"
#include "WinAnimationState.h"

#include "AnimationController.h"
#include "ServiceLocator.h"
#include "SpriteManager.h"
#include "PlayerAnimations.h"

 

WinAnimationState::WinAnimationState(GameStateData * p_data)
	: IGameState(p_data)
{
	m_controllerLevel = new AnimationController();
	m_controllerPlayer = new AnimationController();

	SpriteManager* spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_animationswPtr = ServiceLocator<PlayerAnimations>::GetService();

	m_controllerPlayer->SetAnimation(m_animationswPtr->Still);

	std::string file = "../Assets/level_win.png";
	m_animation = new Animation();
	
	for (int x = 0; x < 2; x++) {
		m_animation->AddFrame(AnimationFrame(
			spriteManager->CreateSprite(file, x * 224, 0, 224, 248),
			Config::WIN_FLASH_SPEED
		));
	}

	m_controllerLevel->SetAnimation(m_animation);
}

WinAnimationState::~WinAnimationState()
{
	delete m_controllerLevel;
	m_controllerLevel = nullptr;

	delete m_controllerPlayer;
	m_controllerPlayer = nullptr;

	delete m_animation;
	m_animation = nullptr;
}

bool WinAnimationState::Update(float p_delta)
{
	m_controllerLevel->Update(p_delta);
	m_controllerPlayer->Update(p_delta);

	return m_pause.Update(p_delta);
}

void WinAnimationState::Draw()
{
	m_controllerLevel->Draw(Vect2(0, 24));
	m_controllerPlayer->Draw(m_datawPtr->m_player->GetScreenLocation());

	m_datawPtr->DrawHUD();
}

void WinAnimationState::Enter()
{
	m_pause.SetPause(Config::WIN_ANIMATION_LENGTH);
}

void WinAnimationState::Exit()
{
}

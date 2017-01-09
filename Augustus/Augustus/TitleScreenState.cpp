#include "stdafx.h"
#include "TitleScreenState.h"
#include "ServiceLocator.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "GameSession.h"
#include "InputManager.h"


TitleScreenState::TitleScreenState()
{
	SpriteManager* spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_inputManager = ServiceLocator<InputManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_BG_Sprite = spriteManager->CreateSprite("../Assets/title_screen.png", 0, 0, 224, 288);
}


TitleScreenState::~TitleScreenState()
{
}

void TitleScreenState::Enter()
{
}

void TitleScreenState::Exit()
{
}

PDA::PDA_ReturnFlag TitleScreenState::Update(float p_delta)
{
	m_drawManager->Draw(m_BG_Sprite, 0, 0);

	if (m_inputManager->IsKeyDownOnce(SDL_SCANCODE_SPACE))
		return PDA::PDA_ReturnFlag::Push;
	
	return PDA::PDA_ReturnFlag::Keep;
}

IState_PDA * TitleScreenState::NextState()
{
	return new GameSession();
}

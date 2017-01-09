#include "stdafx.h"
#include "PacmanGame.h"
#include "IGame.h"
#include "PDA.h"
#include "TitleScreenState.h"

#include "ServiceLocator.h"
#include "GhostAnimations.h"
#include "PlayerAnimations.h"

PacmanGame::PacmanGame()
{
	m_GamePDA = new PDA(new TitleScreenState()); //TODO: initialize with game state

	m_ghostAnimations = new GhostAnimations();
	m_playerAnimations = new PlayerAnimations();
	ServiceLocator<GhostAnimations>::SetService(m_ghostAnimations);
	ServiceLocator<PlayerAnimations>::SetService(m_playerAnimations);
}


PacmanGame::~PacmanGame()
{
	delete m_GamePDA;
	m_GamePDA = nullptr;

	delete m_ghostAnimations;
	m_ghostAnimations = nullptr;
}

void PacmanGame::Enter()
{
}

void PacmanGame::Exit()
{
}

bool PacmanGame::Update(float p_delta)
{
	return m_GamePDA->Update(p_delta);
}
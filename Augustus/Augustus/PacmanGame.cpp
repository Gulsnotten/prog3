#include "stdafx.h"
#include "PacmanGame.h"
#include "IGame.h"
#include "PDA.h"
#include "TitleScreenState.h"

#include "ServiceLocator.h"
#include "GhostAnimations.h"
#include "PlayerAnimations.h"
#include "Font.h"
#include "Highscores.h"

PacmanGame::PacmanGame()
{
	m_GamePDA = new PDA(new TitleScreenState()); //TODO: initialize with game state

	m_ghostAnimations = new GhostAnimations();
	m_playerAnimations = new PlayerAnimations();
	m_font = new Font();
	m_scores = new Highscores();
	ServiceLocator<GhostAnimations>::SetService(m_ghostAnimations);
	ServiceLocator<PlayerAnimations>::SetService(m_playerAnimations);
	ServiceLocator<Font>::SetService(m_font);
	ServiceLocator<Highscores>::SetService(m_scores);
}


PacmanGame::~PacmanGame()
{
	delete m_GamePDA;
	m_GamePDA = nullptr;

	delete m_ghostAnimations;
	m_ghostAnimations = nullptr;

	delete m_font;
	m_font = nullptr;

	delete m_scores;
	m_scores = nullptr;
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

void PacmanGame::Draw()
{
	m_GamePDA->Draw();
}

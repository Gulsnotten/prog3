#include "stdafx.h"
#include "AttractScreenState.h"

#include "ServiceLocator.h"
#include "GhostAnimations.h"
#include "AnimationController.h"
#include "InputManager.h"
#include "Config.h"

#include "Font.h"
#include "BlinkModule.h"

const std::vector<std::string> AttractScreenState::CHARACTERS = {
	"SHADOW",
	"SPEEDY",
	"BASHFUL",
	"POKEY"
};
const std::vector<std::string> AttractScreenState::NICKNAMES = {
	"BLINKY",
	"PINKY",
	"INKY",
	"CLYDE"
};

AttractScreenState::AttractScreenState(GameStateData * p_data)
	: IGameState(p_data)
{
	m_input = ServiceLocator<InputManager>::GetService();

	GhostAnimations* animations = ServiceLocator<GhostAnimations>::GetService();

	for (int i = 0; i < 4; i++) {
		m_ghosts.push_back(new AnimationController());
		m_ghosts.back()->SetAnimation(animations->GetAnimation(Vect2::RIGHT, i));
	}

	m_blinker = new BlinkModule(Config::TEXT_FLASH_SPEED);

	SDL_Color red;
	red.r = 255;
	red.g = 0;
	red.b = 0;
	red.a = 255;

	SDL_Color pink;
	pink.r = 255;
	pink.g = 184;
	pink.b = 255;
	pink.a = 255;

	SDL_Color cyan;
	cyan.r = 1;
	cyan.g = 255;
	cyan.b = 255;
	cyan.a = 255;

	SDL_Color orange;
	orange.r = 255;
	orange.g = 184;
	orange.b = 81;
	orange.a = 255;

	m_colors.clear();
	m_colors.push_back(red);
	m_colors.push_back(pink);
	m_colors.push_back(cyan);
	m_colors.push_back(orange);
}

AttractScreenState::~AttractScreenState()
{
	for (auto g : m_ghosts) {
		delete g;
	}
}

bool AttractScreenState::Update(float p_delta)
{
	m_blinker->Update(p_delta);
	for (auto g : m_ghosts)
		g->Update(p_delta);

	if (m_input->IsKeyDownOnce(SDL_SCANCODE_SPACE)) {
		return false;
	}

	return true;
}

void AttractScreenState::Draw()
{
	m_datawPtr->DrawHUD();

	m_datawPtr->m_fontwPtr->Draw(Vect2(7 * Config::TILE_SIZE, 5 * Config::TILE_SIZE), "CHARACTER / NICKNAME");

	for (unsigned int i = 0; i < m_ghosts.size(); i++) {
		int y = (7 + (i * 3)) * Config::TILE_SIZE;
		m_ghosts[i]->Draw(Vect2(float(4 * Config::TILE_SIZE), float(y - Config::TILE_SIZE / 2)));
		SDL_Color color = m_colors[i];
		m_datawPtr->m_fontwPtr->Draw(Vect2(float(7 * Config::TILE_SIZE), (float)y), "-" + CHARACTERS[i], color);
		m_datawPtr->m_fontwPtr->Draw(Vect2(float(18 * Config::TILE_SIZE), (float)y), "\"" + NICKNAMES[i] + "\"", color);
	}

	if (m_blinker->IsShowing())
		m_datawPtr->m_fontwPtr->DrawCentered(Vect2(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT - (8 * Config::TILE_SIZE)), "PRESS SPACE!");
}

void AttractScreenState::Enter()
{
}

void AttractScreenState::Exit()
{
}

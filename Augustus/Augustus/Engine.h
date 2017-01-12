#pragma once
#include "FPS_Helper.h"

class DrawManager;
class SpriteManager;
class StateManager;
class InputManager;
class SoundManager;
class IGame;

class Engine
{
public:
	Engine();
	~Engine();
	void Initialize(); // Create all manager, initialize SDL
	void Shutdown(); // Delete all managers, shutdown SDL
	void Run(); // Handle all events, calculate delta, update the GAME
	FPS_Helper m_FPShelper;
private:
	void HandleEvents(); // Handles all events from SDL_Pollevents
	void CalculateDeltatime(); // Calculates the time in ms between this and the last
	DrawManager* m_drawManager;
	SpriteManager* m_spriteManager;
	StateManager* m_stateManager;
	InputManager* m_inputManager;
	SoundManager* m_soundManager;
	bool m_running;
	unsigned int m_lastTick;
	float m_delta;

	IGame* m_game;
};

#pragma once

class DrawManager;
class SpriteManager;
class StateManager;
class InputManager;

class Engine {
public:
	Engine();
	~Engine();
	void Initialize(); // create all managers
	void Shutdown(); // delete all managers
	void Run(); // handle all events, calculate delta, update the statemachine
private:
	DrawManager* m_drawManager;
	SpriteManager* m_spriteManager;
	StateManager* m_stateManager;
	InputManager* m_inputManager;
	bool m_running;
	void HandleEvents(); // handles all events from SDL_Pollevents
	void CalculateDeltatime(); // calculates the time in ms between this and the last
};
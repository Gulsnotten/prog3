#pragma once
#include "IGameState.h"
#include <vector>
#include <string>

class AnimationController;
class BlinkModule;

class AttractScreenState : public IGameState
{
private:
	InputManager* m_input;
	std::vector<AnimationController*> m_ghosts;
	BlinkModule* m_blinker;

	static const std::vector<std::string> CHARACTERS;
	static const std::vector<std::string> NICKNAMES;
	std::vector<SDL_Color> m_colors;
public:
	AttractScreenState(GameStateData* p_data);
	~AttractScreenState();

	bool Update(float p_delta);
	void Draw();

	void Enter();
	void Exit();
};
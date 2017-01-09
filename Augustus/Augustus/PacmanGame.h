#pragma once
#include "IGame.h"

class PDA;
class GhostAnimations;
class PlayerAnimations;

class PacmanGame : public IGame
{
public:
	PacmanGame();
	~PacmanGame();

	void Enter();
	void Exit();

	bool Update(float p_delta);
private:
	PDA* m_GamePDA;

	GhostAnimations* m_ghostAnimations;
	PlayerAnimations* m_playerAnimations;
};


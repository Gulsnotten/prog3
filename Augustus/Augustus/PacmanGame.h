#pragma once
#include "IGame.h"

class PDA;
class GhostAnimations;
class PlayerAnimations;
class Font;
class Highscores;

class PacmanGame : public IGame
{
private:
	PDA* m_GamePDA;

	GhostAnimations* m_ghostAnimations;
	PlayerAnimations* m_playerAnimations;
	Font* m_font;
	Highscores* m_scores;
public:
	PacmanGame();
	~PacmanGame();

	void Enter();
	void Exit();

	bool Update(float p_delta);
	void Draw();
};


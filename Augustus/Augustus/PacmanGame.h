#pragma once
#include "IGame.h"

class GameSession;
class GhostAnimations;
class PlayerAnimations;
class Font;
class Highscores;

class PacmanGame : public IGame
{
private:
	GameSession* m_GameFSM;

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


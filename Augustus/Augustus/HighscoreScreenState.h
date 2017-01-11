#pragma once
#include "IState_PDA.h"

class Highscores;
class InputManager;
class Font;
class BlinkModule;

class HighscoreScreenState : public IState_PDA
{
private:
	Highscores* m_highscoreswPtr;
	InputManager* m_input;
	Font* m_fontwPtr;
	BlinkModule* m_blinker;
	SDL_Color m_yellow;
	
	int m_score;
public:
	HighscoreScreenState(int p_score);
	~HighscoreScreenState();

	void Enter();
	void Exit();

	PDA::PDA_ReturnFlag Update(float p_delta);
	void Draw();
	IState_PDA* NextState();
};
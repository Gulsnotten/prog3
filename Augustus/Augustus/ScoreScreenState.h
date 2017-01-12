#pragma once
#include "IGameState.h"

class MusicClip;


class ScoreScreenState : public IGameState
{
private:
	Highscores* m_highscoreswPtr;
	InputManager* m_input;
	BlinkModule* m_blinker;
	SDL_Color m_yellow;
	MusicClip* m_musicwPtr;
public:
	ScoreScreenState(GameStateData* p_data);
	~ScoreScreenState();

	bool Update(float p_delta);
	void Draw();

	void Enter();
	void Exit();
};
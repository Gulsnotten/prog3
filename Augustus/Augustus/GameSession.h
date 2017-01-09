#pragma once
#include "IState_PDA.h"
#include <vector>

class GameStateData;
class IGameState;
class PlayingState;
class StartAnimationState;
class DeathAnimationState;
class WinAnimationState;

class GameSession : public IState_PDA
{
private:
	int m_lives;
	GameStateData* m_data;

	PlayingState* m_playing;
	StartAnimationState* m_startAnimation;
	DeathAnimationState* m_deathAnimation;
	WinAnimationState* m_winAnimation;
	IGameState* m_currentStatewPtr;

	void SwitchState(IGameState* p_state);
public:
	GameSession();
	~GameSession();

	void Enter();
	void Exit();

	PDA::PDA_ReturnFlag Update(float p_delta);
	IState_PDA* NextState();
};


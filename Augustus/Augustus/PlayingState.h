#pragma once
#include "IGameState.h"
#include "Observer.h"
#include <string>
#include "PauseModule.h"

class GhostSoundPicker;

class PlayingState : public IGameState, public Observer
{
private:
	GhostSoundPicker* m_ghostSound;
	PauseModule m_pause;

	void CheckCollision();

	void Win();
	void Lose();
public:
	PlayingState(GameStateData* p_data);
	~PlayingState();

	bool Update(float p_delta);
	void Draw();

	void Enter();
	void Exit();

	void Notify(std::string p_msg);
};
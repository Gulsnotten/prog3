#pragma once

#include "IGameState.h"

class MusicClip;

class StartAnimationState : public IGameState
{
private:
	float m_time;
	MusicClip* m_musicwPtr;

	// Sprite* m_readySprite;
	// Sprite* m_player1Sprite;
public:
	StartAnimationState(GameStateData* p_data);
	~StartAnimationState();

	bool Update(float p_delta);
	void Draw();

	void Enter();
	void Exit();
};

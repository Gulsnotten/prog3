#pragma once

#include "IGameState.h"

class MusicClip;
class Font;
class DrawManager;

class StartAnimationState : public IGameState
{
private:
	float m_time;
	MusicClip* m_musicwPtr;
	DrawManager* m_drawManagerwPtr;

	SDL_Color m_yellow;
public:
	StartAnimationState(GameStateData* p_data);
	~StartAnimationState();

	bool Update(float p_delta);
	void Draw();

	void Enter();
	void Exit();
};

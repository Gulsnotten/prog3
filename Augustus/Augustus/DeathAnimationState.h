#pragma once
#include "IGameState.h"

class AnimationController;
class PlayerAnimations;
class MusicClip;

class DeathAnimationState : public IGameState
{
private:
	AnimationController* m_controller;
	MusicClip* m_musicwPtr;
public:
	DeathAnimationState(GameStateData* p_data);
	~DeathAnimationState();

	bool Update(float p_delta);
	void Draw();

	void Enter();
	void Exit();
};
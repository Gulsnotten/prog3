#pragma once
#include "IGameState.h"
#include "Observer.h"
#include <string>
#include "PauseModule.h"
#include <vector>

class GhostSoundPicker;
class Animation;
class SoundClip;

class PlayingState : public IGameState, public Observer
{
private:
	GhostSoundPicker* m_ghostSound;
	PauseModule m_pause;
	std::vector<Animation*> m_scoreAnimations;
	Animation* m_1UPAnimation;
	SoundClip* m_eatGhostSoundwPtr;

	void CheckCollision();

	void Win();
	void Lose();

	int m_combo;
public:
	PlayingState(GameStateData* p_data);
	~PlayingState();

	bool Update(float p_delta);
	void Draw();

	void Enter();
	void Exit();

	void Notify(std::string p_msg);
};
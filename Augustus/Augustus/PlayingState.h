#pragma once
#include "IGameState.h"
#include <string>
#include "PauseModule.h"
#include <vector>

class GhostSoundPicker;
class Animation;
class SoundClip;

class PlayingState : public IGameState
{
private:
	enum Food { NothingFood, PelletFood, PowerUpFood };

	GhostSoundPicker* m_ghostSound;
	PauseModule m_pause;
	std::vector<Animation*> m_scoreAnimations;
	Animation* m_1UPAnimation;
	SoundClip* m_eatGhostSoundwPtr;
	SoundClip* m_wakaSoundwPtr;
	int m_combo;
	bool m_hasWon;
	bool m_wakaSwitch;

	bool CheckGhostCollision();
	Food CheckFoodCollision();
	
	void Win();
	void Lose();
	void AtePellet();
	void AtePowerup();
	void CheckIfWin();
public:
	PlayingState(GameStateData* p_data);
	~PlayingState();

	bool Update(float p_delta);
	void Draw();

	void Enter();
	void Exit();
};
#pragma once
#include "GameObject.h"
#include "Subject.h"
#include "vect2.h"

class InputManager;
class PlayerAnimations;

class SoundClip;

class Player : public GameObject, public Subject
{
private:
	InputManager* m_inputwPtr;
	PlayerAnimations* m_animationswPtr;
	SoundClip* m_soundwPtr;

	Vect2 m_inputBuffer;
	bool m_isDead;

	void UpdateSound(bool p_bumped);
	void UpdateInput();
public:
	Player(GameObjectData* p_data);
	~Player();

	bool Update(float p_delta);

	void Kill();
	void StopSound();
	bool IsDead();
	Vect2 GetDirection();
};
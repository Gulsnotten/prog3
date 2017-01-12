#pragma once
#include "GameObject.h"
#include "vect2.h"

class InputManager;
class PlayerAnimations;

class SoundClip;

class Player : public GameObject//, public Subject
{
private:
	InputManager* m_inputwPtr;
	PlayerAnimations* m_animationswPtr;

	Vect2 m_inputBuffer;
	bool m_isDead;

	void UpdateInput();
public:
	Player(GameObjectData* p_data);
	~Player();

	bool Update(float p_delta);

	bool SteppedOnTile();

	void Kill();
	bool IsDead();
	Vect2 GetDirection();
};
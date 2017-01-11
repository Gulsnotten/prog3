#pragma once
#include "ICollideable.h"
#include "IAnimationAble.h"
#include "vect2.h"

class Animation;

class PowerUp : public ICollideable, public IAnimationAble
{
	Vect2 m_pos;
	Animation* m_flashAnimation;
public:
	PowerUp(Vect2 p_pos);
	~PowerUp();

	void Update(float p_delta);
	void Draw();
	void ResetAnimation();
};
#pragma once
#include "ICollideable.h"
#include "IAnimationAble.h"
#include "vect2.h"
#include "PauseModule.h"

class FruitAnimations;

class Fruit : public ICollideable, public IAnimationAble
{
	Vect2 m_pos;
	float m_time;
	int m_index;
	bool m_isDead;
	PauseModule m_pauseModule;
	FruitAnimations* m_animationswPtr;
	static const std::vector<int> m_scores;
public:
	Fruit(int p_index);
	~Fruit();

	void Update(float p_delta);
	void Draw();
	void Eat();
	bool IsDead();
	int GetScore();
};
#pragma once
#include "RoamAtRandom_State.h"
#include "vect2.h"
#include "GameObject.h"

class PathFinderModule;

class FleeingState
	: public RoamAtRandom_State
{
private:
	float m_tick;
public:
	FleeingState(GameObjectData* p_data);
	~FleeingState();

	void Enter();

	bool Update(float p_delta);

	bool IsWarning();
};


#pragma once
#include "IGhostState.h"
#include "GameObject.h"

class Vect2;

class RoamAtRandom_State :
	public IGhostState
{
protected:
	Vect2 GetRandomDir();
	Vect2 GetRandomDir(Vect2 p_banned);
public:
	RoamAtRandom_State(GameObjectData* p_data);
	virtual ~RoamAtRandom_State();

	bool Update(float p_delta);
};


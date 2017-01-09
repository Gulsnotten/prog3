#pragma once
#include "IRoamingState.h"
#include "GameObject.h"

class Vect2;

class RoamAtRandom_State :
	public IRoamingState
{
protected:
	GameObjectData* m_datawPtr;

	Vect2 GetRandomDir();
	Vect2 GetRandomDir(Vect2 p_banned);
public:
	RoamAtRandom_State(GameObjectData* p_data);
	virtual ~RoamAtRandom_State();

	bool Update(float p_delta);
	void Draw();
};


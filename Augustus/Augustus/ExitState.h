#pragma once
#include "IState.h"
#include "vect2.h"
#include "GameObject.h"

class ExitState :
	public IState
{
private:
	GameObjectData* m_datawPtr;

	Vect2 m_currentDirection;
public:
	ExitState(GameObjectData* p_data);
	~ExitState();

	bool Update(float p_delta);
	void Draw();

	Vect2 GetDirection();
};


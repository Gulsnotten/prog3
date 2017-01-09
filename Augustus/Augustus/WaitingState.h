#pragma once
#include "IState.h"
#include "vect2.h"
#include "GameObject.h"

class WaitingState :
	public IState
{
private:
	bool m_goingUp;
	GameObjectData* m_datawPtr;
	int m_wait;
public:
	WaitingState(GameObjectData* p_data);
	~WaitingState();

	void Initialize(int p_wait);

	bool Update(float p_delta);
	void Draw();

	Vect2 GetDirection();
};


#pragma once
#include "IRoamingState.h"
#include <vector>

class AmbushState;
class ChaseState;
class RoamAtRandom_State;

class RandomBehaviorState :
	public IRoamingState
{
private:
	std::vector<IState*> m_behaviors;

	IState* m_currentState;

	void SwitchState();
public:
	RandomBehaviorState(AmbushState* p_ambush, ChaseState* p_chase,
		RoamAtRandom_State* p_roamRandom);
	~RandomBehaviorState();

	bool Update(float p_delta);
	void Draw();
};


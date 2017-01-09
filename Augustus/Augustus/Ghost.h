#pragma once
#include "GameObject.h"

class IState;
class Level;
class GhostAnimations;

class IRoamingState;
class WaitingState;
class ExitState;
class FleeingState;
class RunToHouseState;

class Ghost : public GameObject
{
private:
	WaitingState* m_waiting;
	ExitState* m_exitHouse;
	IRoamingState* m_roaming;
	FleeingState* m_fleeing;
	RunToHouseState* m_runToHouse;
	IState* m_currentStatewPtr;

	GhostAnimations* m_animationswPtr;

	int m_color;

	void SwitchState(IState* p_state);
	void SetAnimation();
public:
	Ghost(GameObjectData* p_data, IRoamingState * p_roaming, Vect2* p_playerPos, int p_color);
	virtual ~Ghost();

	virtual bool Update(float p_delta);

	void StartRoaming();
	void StartWaiting(int p_wait);
	void Flee();
	void RunToHouse();

	bool IsFleeing();
	bool IsDead();
};


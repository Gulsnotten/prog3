#pragma once
#include "IRoamingState.h"
#include "vect2.h"
#include "GameObject.h"

class PathFinderModule;

class ChaseState :
	public IRoamingState
{
private:
	PathFinderModule* m_pathfinder;
	GameObjectData* m_datawPtr;
	Vect2* m_targetwPtr;
public:
	ChaseState(GameObjectData* p_data, Vect2* p_target);
	~ChaseState();

	void Enter();
	void OnSpawn();

	bool Update(float p_delta);
	void Draw();
};


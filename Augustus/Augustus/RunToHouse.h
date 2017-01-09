#pragma once
#include "IState.h"
#include "vect2.h"
#include "GameObject.h"

class PathFinderModule;
class Level;

class RunToHouseState :
	public IState
{
private:
	static const Vect2 FRONT_OF_HOUSE;

	PathFinderModule* m_pathfinder;
	GameObjectData* m_datawPtr;

	bool m_done;
public:
	RunToHouseState(GameObjectData* p_data);
	~RunToHouseState();

	bool Update(float p_delta);
	void Draw();

	void Enter();
};


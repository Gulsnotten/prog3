#pragma once
#include "IRoamingState.h"
#include "vect2.h"
#include "GameObject.h"

class PathFinderModule;
class Player;

class AmbushState :
	public IRoamingState

{
private:
	PathFinderModule* m_pathfinder;
	GameObjectData* m_datawPtr;
	Player* m_playerwPtr;

	Vect2 m_currentTarget;

	bool IsIntersection(Vect2 p_pos);
	Vect2 NextIntersection(Vect2 p_pos, Vect2 p_dir);

	Vect2 GetNextTarget();
	void UpdatePath();
public:
	AmbushState(GameObjectData* p_data, Player* p_player);
	~AmbushState();

	bool Update(float p_delta);
	void Draw();

	void Enter();
	void OnSpawn();
};


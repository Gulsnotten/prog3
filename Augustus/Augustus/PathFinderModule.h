#pragma once
#include "vect2.h"
#include "Tile.h"
#include <vector>

#include <map>

class Level;

#include <list>
struct Ticket {
	int heat;
	Vect2 pos;

	Ticket(int p_heat, Vect2 p_pos)
		: heat(p_heat), pos(p_pos)
	{

	}
};

class PathFinderModule
{
private:
	Level* m_levelwPtr;
	std::vector<std::vector<int>> m_heatMap;
	std::list<Ticket> m_bucket;

	std::vector<Vect2> m_banned_pos;
public:
	PathFinderModule(Level* p_level);
	~PathFinderModule();

	void UpdatePath(Vect2 p_target);
	void UpdatePath(Vect2 p_target, Vect2 p_banned_position);
	void UpdatePath(Vect2 p_target, std::vector<Vect2> p_banned_positions);
	Vect2 GetNextDir(Vect2 p_pos);
	Vect2 GetNextDir(Vect2 p_pos, Vect2 p_banned_dir);
	Vect2 GetNextDir(Vect2 p_pos, std::vector<Vect2> p_banned_directions);

	bool ReachedGoal(Vect2 p_pos);
};


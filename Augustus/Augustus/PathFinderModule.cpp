#include "stdafx.h"
#include "PathFinderModule.h"

#include "Level.h"
 

PathFinderModule::PathFinderModule(Level * p_level)
	: m_levelwPtr(p_level)
{
}

PathFinderModule::~PathFinderModule()
{
}

void PathFinderModule::UpdatePath(Vect2 p_target)
{
	UpdatePath(p_target, std::vector<Vect2>()); // no banned
}

void PathFinderModule::UpdatePath(Vect2 p_target, Vect2 p_banned_position)
{
	UpdatePath(p_target, std::vector<Vect2> {p_banned_position});
}

void PathFinderModule::UpdatePath(Vect2 p_target, std::vector<Vect2> p_banned_positions)
{
	Vect2 target = p_target.Round().CorrectTeleport();

	m_banned_pos.clear();
	for (auto p : p_banned_positions)
		m_banned_pos.push_back(p.Round().CorrectTeleport());

	m_heatMap.clear();

	for (int y = 0; y < Config::LEVEL_HEIGHT; y++) {
		m_heatMap.push_back(std::vector<int>());
		for (int x = 0; x < Config::LEVEL_WIDTH; x++) {
			m_heatMap.back().push_back(999999);
		}
	}

	m_bucket.clear();
	m_bucket.push_front(Ticket(0, target));
	m_heatMap[(int)target.y][(int)target.x] = 0;

	while (m_bucket.size() != 0) {
		Ticket t = m_bucket.front();
		int newHeat = t.heat + 1;

		for (auto d : m_levelwPtr->AvailableDirections(t.pos)) {
			Vect2 pos = t.pos + d;
			pos = pos.CorrectTeleport();

			bool banned = false;
			for (auto b : m_banned_pos) {
				if (b == pos)
					banned = true;
			}

			if (!banned && m_heatMap[(int)pos.y][(int)pos.x] > newHeat) {
				m_heatMap[(int)pos.y][(int)pos.x] = newHeat;

				m_bucket.push_back(Ticket(newHeat, pos));
			}
		}

		m_bucket.pop_front();
	}
}

Vect2 PathFinderModule::GetNextDir(Vect2 p_pos)
{
	assert(m_heatMap.size() > 0); // call UpdatePath first!!

	Vect2 ret = Vect2::ZERO;
	int heat = 99999;

	for (auto d : m_levelwPtr->AvailableDirections(p_pos.Round())) {
		Vect2 pos = p_pos.Round() + d;
		pos = pos.CorrectTeleport();

		int h = m_heatMap[(int)pos.y][(int)pos.x];

		if (h < heat) {
			heat = h;
			ret = d;
		}
	}

	return ret;
}

bool PathFinderModule::ReachedGoal(Vect2 p_pos)
{
	Vect2 pos = p_pos.Round().CorrectTeleport();

	return m_heatMap[(int)pos.y][(int)pos.x] == 0;
}

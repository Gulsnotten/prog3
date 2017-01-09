#include "stdafx.h"
#include "AmbushState.h"

#include "Level.h"
#include "MovementModule.h"
#include "Player.h"
#include "PathFinderModule.h"

#include "Config.h"


bool AmbushState::IsIntersection(Vect2 p_pos)
{
	Vect2 pos = p_pos.Round();

	std::vector<Vect2> dirs = m_datawPtr->m_levelwPtr->AvailableDirections(pos);

	//intersection
	if (dirs.size() > 2)
		return true;

	// corner
	bool x = false;
	bool y = false;
	for (auto d : dirs) {
		if (d.x != 0)
			x = true;
		if (d.y != 0)
			y = true;
	}
	if (x && y)
		return true;

	//corridor :(
	return false;
}

Vect2 AmbushState::NextIntersection(Vect2 p_pos, Vect2 p_dir)
{
	Vect2 pos = p_pos.Round();

	if (p_dir == Vect2::ZERO) {
		return pos;
	}

	while (!IsIntersection(pos)) {
		pos += p_dir;
		pos = pos.CorrectTeleport();
	}

	return pos;
}

Vect2 AmbushState::GetNextTarget()
{
	Vect2 next = NextIntersection(*m_playerwPtr->GetPos(), m_playerwPtr->GetDirection());

	// if ghost is on target it will stop, so it sets the target to the player
	if (next == m_datawPtr->m_pos->Round()) {
		return m_playerwPtr->GetPos()->Round();
	}

	return next;
}

void AmbushState::UpdatePath()
{
	m_currentTarget = GetNextTarget();
	m_pathfinder->UpdatePath(m_currentTarget, *m_playerwPtr->GetPos());
}


AmbushState::AmbushState(GameObjectData* p_data, Player* p_player)
	: m_datawPtr(p_data), m_playerwPtr(p_player)
{
	m_pathfinder = new PathFinderModule(m_datawPtr->m_levelwPtr);

	UpdatePath();
}

AmbushState::~AmbushState()
{
	delete m_pathfinder;
	m_pathfinder = nullptr;
}

bool AmbushState::Update(float p_delta)
{
	Vect2* pos = m_datawPtr->m_pos;

	Vect2 nextDir = m_pathfinder->GetNextDir(*pos);

	m_datawPtr->m_movement->Update(p_delta, nextDir, float(Config::MOVEMENT_SPEED));

	if (m_pathfinder->ReachedGoal(*m_datawPtr->m_pos)) {
		UpdatePath();
		return false;
	}

	return true;
}

void AmbushState::Draw()
{
}

void AmbushState::Enter()
{
	UpdatePath();
}

void AmbushState::OnSpawn()
{
	m_currentTarget = Vect2((float)Level::WIDTH - 2, 1);
	m_pathfinder->UpdatePath(m_currentTarget, *m_playerwPtr->GetPos());
}

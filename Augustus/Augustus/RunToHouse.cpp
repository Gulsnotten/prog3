#include "stdafx.h"
#include "RunToHouse.h"

#include "MovementModule.h"
#include "PathFinderModule.h"
#include "Level.h"

#include "Config.h"

const Vect2 RunToHouseState::FRONT_OF_HOUSE = Vect2(14, 11);

RunToHouseState::RunToHouseState(GameObjectData* p_data)
{
	m_datawPtr = p_data;

	m_pathfinder = new PathFinderModule(m_datawPtr->m_levelwPtr);
	m_pathfinder->UpdatePath(FRONT_OF_HOUSE);
}

RunToHouseState::~RunToHouseState()
{
	delete m_pathfinder;
	m_pathfinder = nullptr;
}

bool RunToHouseState::Update(float p_delta)
{
	float speed = Config::MOVEMENT_SPEED_FAST;

	Vect2* pos = m_datawPtr->m_pos;

	if (m_pathfinder->ReachedGoal(*pos) ||
		FRONT_OF_HOUSE.Floor() == pos->Floor())
	{
		m_done = true;
	}

	if (m_done) {
		if (pos->x == Level::CENTER) {
			if (pos->y == Level::HOUSE_Y) {
				return false;
			}
			else
			{
				pos->GotoY(Level::HOUSE_Y, speed * p_delta);
			}
		}
		else {
			pos->GotoX(Level::CENTER, speed * p_delta);
		}
	}
	else
	{
		m_datawPtr->m_movement->Update(p_delta, m_pathfinder->GetNextDir(*pos), speed);
	}

	return true;
}

void RunToHouseState::Draw()
{
}

void RunToHouseState::Enter()
{
	m_done = false;
}

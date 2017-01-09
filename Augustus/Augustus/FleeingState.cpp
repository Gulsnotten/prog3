#include "stdafx.h"
#include "FleeingState.h"


#include "PathFinderModule.h"
#include "MovementModule.h"

#include "Config.h"


FleeingState::FleeingState(GameObjectData* p_data)
	: RoamAtRandom_State(p_data)
{
}

FleeingState::~FleeingState()
{
}

void FleeingState::Enter()
{
	m_datawPtr->m_movement->TurnAround();
	m_tick = 0;
}

bool FleeingState::Update(float p_delta)
{
	float subspeed = float(Config::MOVEMENT_SPEED_SLOW) / float(Config::MOVEMENT_SPEED);
	RoamAtRandom_State::Update(p_delta * subspeed);

	m_tick += p_delta;

	return m_tick < Config::FLEEING_TIME + Config::WARNING_TIME;
}

bool FleeingState::IsWarning()
{
	return m_tick > Config::FLEEING_TIME;
}

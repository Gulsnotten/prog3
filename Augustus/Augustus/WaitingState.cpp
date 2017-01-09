#include "stdafx.h"
#include "WaitingState.h"

#include "Level.h"
#include "MovementModule.h"

#include "Config.h"


WaitingState::WaitingState(GameObjectData* p_data)
{
	m_datawPtr = p_data;
	m_wait = 0;
	m_goingUp = true;
}

WaitingState::~WaitingState()
{
}

void WaitingState::Initialize(int p_wait)
{
	m_wait = p_wait;
}

bool WaitingState::Update(float p_delta)
{
	Vect2* pos = m_datawPtr->m_pos;

	float top = Level::HOUSE_Y + 0.5f;
	float bottom = Level::HOUSE_Y - 0.5f;

	if (m_goingUp) {
		if (pos->y == top) {
			m_goingUp = false;
			m_wait--;
		}
		else {
			pos->GotoY(top, Config::MOVEMENT_SPEED_SLOW * p_delta);
		}
	}
	else {
		if (pos->y == bottom) {
			m_goingUp = true;
			m_wait--;
		}
		else {
			pos->GotoY(bottom, Config::MOVEMENT_SPEED_SLOW * p_delta);
		}
	}

	return (m_wait > 0);
}

void WaitingState::Draw()
{
}

Vect2 WaitingState::GetDirection()
{
	if (m_goingUp) {
		return Vect2::UP;
	}
	else {
		return Vect2::DOWN;
	}
}

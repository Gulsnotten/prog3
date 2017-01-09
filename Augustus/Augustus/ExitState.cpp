#include "stdafx.h"
#include "ExitState.h"

#include "Level.h"
#include "MovementModule.h"

#include "Config.h"

ExitState::ExitState(GameObjectData* p_data)
	: m_datawPtr(p_data)
{
	m_currentDirection = Vect2::ZERO;
}

ExitState::~ExitState()
{
}

bool ExitState::Update(float p_delta)
{
	float speed = Config::MOVEMENT_SPEED_SLOW;

	Vect2* pos = m_datawPtr->m_pos;

	if (pos->y == Level::HOUSE_EXIT_Y)
		return false; // switch state !!

	if (pos->x != Level::CENTER) {
		if (pos->y != Level::HOUSE_Y) {
			//for animations
			if (pos->y > Level::HOUSE_Y) {
				m_currentDirection = Vect2::UP;
			}
			else {
				m_currentDirection = Vect2::DOWN;
			}

			pos->GotoY(Level::HOUSE_Y, speed * p_delta);
		}
		else {
			if (pos->x < Level::CENTER) {
				m_currentDirection = Vect2::RIGHT;
			}
			else {
				m_currentDirection = Vect2::LEFT;
			}

			pos->GotoX(Level::CENTER, speed * p_delta);
		}
	}
	else if (pos->y != Level::HOUSE_EXIT_Y) {
		pos->GotoY(Level::HOUSE_EXIT_Y, speed * p_delta);

		m_currentDirection = Vect2::UP;
	}

	return true;
}

void ExitState::Draw()
{
}

Vect2 ExitState::GetDirection()
{
	return m_currentDirection;
}

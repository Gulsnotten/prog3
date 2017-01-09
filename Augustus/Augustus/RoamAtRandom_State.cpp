#include "stdafx.h"
#include "RoamAtRandom_State.h"

#include "MovementModule.h"
#include <random>
#include "Level.h"

#include "Config.h"

Vect2 RoamAtRandom_State::GetRandomDir()
{
	int r = rand() % 4;

	switch (r) {
	case 0:
		return Vect2(0, -1);
	case 1:
		return Vect2(0, 1);
	case 2:
		return Vect2(-1, 0);
	case 3:
		return Vect2(1, 0);
	default:
		return Vect2::ZERO;
	}
}

Vect2 RoamAtRandom_State::GetRandomDir(Vect2 p_banned)
{
	Vect2 ret = Vect2(p_banned.x, p_banned.y);

	while (ret == p_banned) {
		ret = GetRandomDir();
	}

	return ret;
}

RoamAtRandom_State::RoamAtRandom_State(GameObjectData* p_data)
{
	m_datawPtr = p_data;
}

RoamAtRandom_State::~RoamAtRandom_State()
{
}

bool RoamAtRandom_State::Update(float p_delta)
{
	bool bumped;

	Vect2* pos = m_datawPtr->m_pos;

	if (m_datawPtr->m_movement->SteppedOnTile()) {
		Vect2 back = m_datawPtr->m_movement->GetDirection();
		back.x *= -1;
		back.y *= -1;

		Vect2 newDir = Vect2::ZERO;
		bool contains = false;
		while (!contains) {
			newDir = GetRandomDir(back);
			for (auto v : m_datawPtr->m_movement->AvailableDirections(pos->Round())) {
				if (v == newDir)
					contains = true;
			}
		}

		bumped = m_datawPtr->m_movement->Update(p_delta, newDir, 8);
	}
	else {
		Vect2 dir = m_datawPtr->m_movement->GetDirection();
		if (dir == Vect2::ZERO) {
			std::vector<Vect2> dirs = m_datawPtr->m_movement->AvailableDirections(*pos);
			int r = rand() % dirs.size();

			dir = dirs[r];
		}
		bumped = m_datawPtr->m_movement->Update(p_delta, dir, (float)Config::MOVEMENT_SPEED);
	}

	return !bumped;
}

void RoamAtRandom_State::Draw()
{
}

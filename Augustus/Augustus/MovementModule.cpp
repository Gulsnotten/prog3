#include "stdafx.h"
#include "MovementModule.h"

#include "Level.h"
#include "Tile.h"


bool MovementModule::IsDirAvailable(Vect2 p_dir)
{
	std::vector<Vect2> available = AvailableDirections(*m_positionwPtr);

	for (auto a : available) {
		if (a == p_dir)
			return true;
	}

	return false;
}

void MovementModule::CheckWarp()
{
	//teleport
	if (m_positionwPtr->x < -1)
		m_positionwPtr->x += Level::WIDTH + 1;
	if (m_positionwPtr->x > Level::WIDTH)
		m_positionwPtr->x -= Level::WIDTH + 1;
}

void MovementModule::OnStep(Vect2 p_dir)
{
	if (IsDirAvailable(p_dir)) {
		m_direction = p_dir;

		if (m_direction.x == 0) {
			m_positionwPtr->x = m_positionwPtr->Round().x;
		}
		if (m_direction.y == 0) {
			m_positionwPtr->y = m_positionwPtr->Round().y;
		}
	}
}


MovementModule::MovementModule(Level * p_level, Vect2* p_pos)
	: m_levelwPtr(p_level), m_positionwPtr(p_pos), m_direction(Vect2::ZERO),
	m_steppedOnTile(false), m_bumpedLastFrame(false)
{
}

MovementModule::MovementModule(Level * p_level, Vect2 * p_pos, Vect2 p_dir)
	: MovementModule(p_level, p_pos)
{
	m_direction = p_dir;
}

MovementModule::~MovementModule()
{
}

void MovementModule::TurnAround()
{
	m_direction.x *= -1;
	m_direction.y *= -1;
}

bool MovementModule::Update(float p_delta, Vect2 p_bufferedInput, float p_speed) // returns true when bumping into wall
{
	bool bumped = false;

	if (SteppedOnTile()) {
		OnStep(p_bufferedInput);
	}

	//turn around
	if (p_bufferedInput + m_direction == Vect2::ZERO) {
		m_direction = p_bufferedInput;
	}

	Vect2 change_pos = Vect2(
		p_speed * p_delta * m_direction.x,
		p_speed * p_delta * m_direction.y);

	Vect2 new_pos = *m_positionwPtr + change_pos;

	Vect2 test = new_pos.Round();
	Vect2 test2 = new_pos + Vect2(0,0);
	Vect2 test3 = test2.Round();

	Vect2 facing_tile = new_pos.Round() + m_direction;
	facing_tile.Round();

	if (m_levelwPtr->GetTile(facing_tile).collision()) {
		float dis_y = new_pos.x - facing_tile.x;
		float dis_x = new_pos.y - facing_tile.y;
		if (std::sqrt((dis_x * dis_x) + (dis_y * dis_y)) <= 1) {
			new_pos.x = facing_tile.x - m_direction.x;
			new_pos.y = facing_tile.y - m_direction.y;

			bumped = true;
		}
	}
	
	Vect2 start_pos = *m_positionwPtr;
	*m_positionwPtr = new_pos;

	// intersection (or middle of tile)
	if (!SteppedOnTile()) {
		Vect2 offset = m_positionwPtr->GetOffset();
		if ((offset.x == 0 && offset.y == 0) ||
			start_pos.Floor() != m_positionwPtr->Floor() ||
			m_direction == Vect2::ZERO)
		{

			m_steppedOnTile = true;
		}
	}
	else
		m_steppedOnTile = false;

	if (m_positionwPtr->x < 0 || m_positionwPtr->x >= m_levelwPtr->WIDTH - 1)
		m_steppedOnTile = false;

	CheckWarp();

	bool ret = bumped && m_bumpedLastFrame;
	m_bumpedLastFrame = bumped;
	return ret;
}

Vect2 MovementModule::GetDirection()
{
	return m_direction;
}

std::vector<Vect2> MovementModule::AvailableDirections(Vect2 p_pos)
{
	return m_levelwPtr->AvailableDirections(p_pos);
}

bool MovementModule::SteppedOnTile()
{
	return m_steppedOnTile;
}
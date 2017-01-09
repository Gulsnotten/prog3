#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
{
}

Tile::Tile(TileType p_type) : m_type(p_type)
{
}

Tile::~Tile()
{
	
}

TileType Tile::GetType()
{
	return m_type;
}

bool Tile::collision()
{
	switch (m_type) {
	case TileType::Empty:
	case TileType::Pellet:
	case TileType::Powerup:
		return false;
	case TileType::Wall:
		return true;
	}
	return true;
}

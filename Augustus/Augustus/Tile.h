#pragma once
#include "ICollideable.h"

enum TileType { Empty, Wall, Pellet, Powerup };

class Tile : public ICollideable
{
private:
	TileType m_type;
	void Tile::SetPos(int p_x, int p_y);
public:
	Tile();
	Tile(TileType p_type);
	Tile(TileType p_type, int p_x, int p_y);
	~Tile();

	TileType GetType() const;
	bool collision() const;
	void ChangeType(TileType p_type);
};


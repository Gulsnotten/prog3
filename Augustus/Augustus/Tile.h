#pragma once

enum TileType { Empty, Wall, Pellet, Powerup };

class Tile
{
private:
	TileType m_type;
public:
	Tile();
	Tile(TileType p_type);
	~Tile();

	TileType GetType();
	bool collision();
};


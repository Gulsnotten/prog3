#include "stdafx.h"
#include "Level.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Tile.h"

#include "ServiceLocator.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Sprite.h"

#include "vect2.h"

const int	Level::WIDTH = 28,
			Level::HEIGHT = 31;
			
const float Level::CENTER = WIDTH / 2.0f - 0.5f,
			Level::HOUSE_Y = 14,
			Level::HOUSE_EXIT_Y = 11;


Tile Level::charToTile(char c)
{
	assert(c == 'w' || c == ' ' || c == '.' || c == 'P');

	switch (c) {
	case 'w':
		return Tile(TileType::Wall);
	case ' ':
		return Tile(TileType::Empty);
	case '.':
		return Tile(TileType::Pellet);
	case 'P':
		return Tile(TileType::Powerup);
	}

	return Tile();
}

Level::Level(){
	SpriteManager* spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_pelletSprite = spriteManager->CreateSprite("../Assets/pellet.png", 0, 0, 8, 8);
	m_powerupSprite = spriteManager->CreateSprite("../Assets/pellet.png", 8, 0, 8, 8);
}


Level::~Level()
{
}

void Level::LoadLevel()
{
	std::vector<std::string> raw_level;
	raw_level.clear();

	std::ifstream file("../Assets/level.txt");
	assert(file.is_open());
	std::string line;
	while (std::getline(file, line))
	{
		//std::cout << line << '\n';
		raw_level.push_back(line);
	}
	file.close();

	for (auto str : raw_level)
		std::cout << str << '\n';

	m_tiles.clear();
	m_pelletsCount = 0;

	for (auto str : raw_level) {
		std::vector<Tile> row;
		for (auto c : str) {
			Tile tile = charToTile(c);

			row.push_back(tile);

			if (tile.GetType() == TileType::Pellet ||
				tile.GetType() == TileType::Powerup)
			{
				m_pelletsCount++;
			}
		}
		m_tiles.push_back(row);
	}
}

void Level::DrawPellets(const int &p_x, const int &p_y)
{
	int y = 0;
	for (auto arr : m_tiles) {
		int x = 0;
		for (auto t : arr) {

			int posx = p_x + (x * 8);
			int posy = p_y + (y * 8);

			if (t.GetType() == TileType::Pellet) {
				m_drawManager->Draw(m_pelletSprite, posx, posy);
			}
			if (t.GetType() == TileType::Powerup) {
				m_drawManager->Draw(m_powerupSprite, posx, posy);
			}
			x++;
		}
		y++;
	}
}

Tile Level::GetTile(Vect2 p_vect2)
{
	p_vect2.x = (float)floor(p_vect2.x);
	p_vect2.y = (float)floor(p_vect2.y);

	if (p_vect2.x < 0 || p_vect2.y < 0 ||
		p_vect2.x >= WIDTH || p_vect2.y >= HEIGHT)
	{
		return Tile(TileType::Empty);
	}

	return m_tiles[(int)p_vect2.y][(int)p_vect2.x];
}

void Level::ReplaceTile(Vect2 p_vect2, Tile p_tile)
{
	p_vect2 = p_vect2.Round();

	int x = (int)p_vect2.x;
	int y = (int)p_vect2.y;

	Tile oldTile = m_tiles[y][x];

	if (oldTile.GetType() == TileType::Pellet ||
		oldTile.GetType() == TileType::Powerup)
	{
		m_pelletsCount--;
	}

	m_tiles[y][x] = p_tile;
}

std::vector<Vect2> Level::AvailableDirections(Vect2 p_pos)
{
	std::vector<Vect2> ret;
	bool up = true;
	bool down = true;
	bool left = true;
	bool right = true;

	Vect2 onTile = p_pos.Round();
	Vect2 offset = p_pos.GetOffset();

	if (GetTile(Vect2(onTile.x, onTile.y - 1)).collision()) {
		if (offset.y > 0)
			up = true;
		else
			up = false;
	}

	if (GetTile(Vect2(onTile.x, onTile.y + 1)).collision()) {
		if (offset.y < 0)
			down = true;
		else
			down = false;
	}

	if (GetTile(Vect2(onTile.x - 1, onTile.y)).collision()) {
		if (offset.x > 0)
			left = true;
		else
			left = false;
	}

	if (GetTile(Vect2(onTile.x + 1, onTile.y)).collision()) {
		if (offset.x < 0)
			right = true;
		else
			right = false;
	}

	if (up) {
		ret.push_back(Vect2::UP);
	}
	if (down) {
		ret.push_back(Vect2::DOWN);
	}
	if (left) {
		ret.push_back(Vect2::LEFT);
	}
	if (right) {
		ret.push_back(Vect2::RIGHT);
	}

	return ret;
}

bool Level::IsIntersection(Vect2 p_pos)
{
	std::vector<Vect2> dirs = AvailableDirections(p_pos);

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

int Level::PelletsCount()
{
	return m_pelletsCount;
}

#include "stdafx.h"
#include "Level.h"

#include <string>
#include <vector>

#include "Tile.h"

#include "ServiceLocator.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Sprite.h"

#include "vect2.h"

#include "TextLoader.h"
#include <iostream>

#include "PowerUp.h"
 

#include "CollisionManager.h"
#include "Player.h"


Tile* Level::charToTile(char c, int p_x, int p_y)
{
	assert(c == 'w' || c == ' ' || c == '.' || c == 'P');

	switch (c) {
	case 'w':
		return new Tile(TileType::Wall, p_x, p_y);
	case ' ':
		return new Tile(TileType::Empty, p_x, p_y);
	case '.':
		return new Tile(TileType::Pellet, p_x, p_y);
	case 'P':
		return new Tile(TileType::Powerup, p_x, p_y);
	}

	return new Tile();
}

void Level::DeletePowerUps()
{
	for (auto p : m_powerUps) {
		if (p != nullptr) {
			delete p;
			p = nullptr;
		}
	}
	m_powerUps.clear();
}

int Level::CorrectTeleportAxis(const int & p_a, const int & p_max) const
{
	int a = p_a;
	if (a < 0)
		a += p_max;
	if (a >= p_max)
		a -= p_max;

	return a;
}

bool Level::IsBanned(const Vect2 & p_pos, const std::vector<Vect2>& p_banned) const
{
	Vect2 pos = p_pos.Round().CorrectTeleport();

	for (auto b : p_banned) {
		if (b == pos)
			return true;
	}

	return false;
}

Level::Level(){
	SpriteManager* spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManagerwPtr = ServiceLocator<DrawManager>::GetService();
	m_pelletSprite = spriteManager->CreateSprite("../Assets/pellet.png", 0, 0, 8, 8);
	m_powerupSprite = spriteManager->CreateSprite("../Assets/pellet.png", 8, 0, 8, 8);
	m_levelSpritewPtr = spriteManager->CreateSprite("../Assets/level.png", 0, 0, 224, 248);
}


Level::~Level()
{
}

void Level::LoadLevel()
{
	std::vector<std::string> raw_level = TextFileManipulator::LoadFile("../Assets/level.txt");

	for (auto str : raw_level)
		std::cout << str << '\n';

	m_tiles.clear();
	DeletePowerUps();

	m_pelletsCount = 0;

	int y = 0;
	for (auto str : raw_level) {
		int x = 0;
		std::vector<Tile*> row;
		for (auto c : str) {
			Tile* tile = charToTile(c, x, y);

			if (tile->GetType() == TileType::Pellet)
			{
				m_pelletsCount++;
			}

			if (tile->GetType() == TileType::Powerup) {
				m_powerUps.push_back(
					new PowerUp(Vect2((float)x * Config::TILE_SIZE, (float)y * Config::TILE_SIZE + 24))
				);
			}

			row.push_back(tile);

			x++;
		}
		m_tiles.push_back(row);
		y++;
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

			if (t->GetType() == TileType::Pellet) {
				m_drawManagerwPtr->Draw(m_pelletSprite, posx, posy);
			}
			x++;
		}
		y++;
	}
}

Tile* Level::GetTile(Vect2 p_vect2)
{
	return GetTile(int(p_vect2.x), int(p_vect2.y));
}

Tile* Level::GetTile(int p_x, int p_y)
{
	int x = p_x;
	int y = p_y;

	if (x >= Config::LEVEL_WIDTH)
		x -= Config::LEVEL_WIDTH;
	if (x < 0)
		x += Config::LEVEL_WIDTH;

	if (y >= Config::LEVEL_HEIGHT)
		y -= Config::LEVEL_HEIGHT;
	if (y < 0)
		y += Config::LEVEL_HEIGHT;
	return m_tiles[y][x];
}

void Level::EatTile(Tile* p_tile)
{
	if (p_tile->GetType() == TileType::Pellet
		//|| oldTile->GetType() == TileType::Powerup
		)
	{
		m_pelletsCount--;

		p_tile->ChangeType(Empty);
	}
}

bool Level::PelletCollision(Player * p_player)
{
	Vect2 pos = p_player->GetPos()->Round().CorrectTeleport();

	std::vector<Tile*> checkTiles;
	checkTiles.push_back(GetTile(pos));
	checkTiles.push_back(GetTile(pos + p_player->GetDirection()));

	for (unsigned int i = 0; i < checkTiles.size(); i++) {
		Tile* tile = checkTiles[i];

		if (tile->GetType() == Pellet && CollisionManager::CheckCollision(p_player, checkTiles[i])) {

			EatTile(tile);
			return true;
		}
	}

	return false;
}

bool Level::PowerUpCollision(ICollideable * p_other)
{
	bool collided = false;

	for (unsigned int i = 0; i < m_powerUps.size(); i++) {
		PowerUp* powerup = m_powerUps[i];

		if (CollisionManager::CheckCollision(powerup, p_other)) {
			collided = true;

			delete powerup;
			m_powerUps[i] = nullptr;

			auto it = m_powerUps.begin();
			m_powerUps.erase(it + i);
			i--;
		}
	}

	return collided;
}

std::vector<Vect2> Level::AvailableDirections(const Vect2& p_pos)
{
	std::vector<Vect2> ret;
	bool up = true;
	bool down = true;
	bool left = true;
	bool right = true;

	Vect2 onTile = p_pos.Round();
	Vect2 offset = p_pos.GetOffset();

	if (GetTile(Vect2(onTile.x, onTile.y - 1))->collision()) {
		if (offset.y > 0)
			up = true;
		else
			up = false;
	}

	if (GetTile(Vect2(onTile.x, onTile.y + 1))->collision()) {
		if (offset.y < 0)
			down = true;
		else
			down = false;
	}

	if (GetTile(Vect2(onTile.x - 1, onTile.y))->collision()) {
		if (offset.x > 0)
			left = true;
		else
			left = false;
	}

	if (GetTile(Vect2(onTile.x + 1, onTile.y))->collision()) {
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

std::vector<Vect2> Level::AvailableDirections(const int& p_x, const int& p_y)
{
	std::vector<Vect2> ret;

	if (!GetTile(p_x, p_y - 1)->collision()) {
		ret.push_back(Vect2::UP);
	}
	if (!GetTile(p_x, p_y + 1)->collision()) {
		ret.push_back(Vect2::DOWN);
	}
	if (!GetTile(p_x - 1, p_y)->collision()) {
		ret.push_back(Vect2::LEFT);
	}
	if (!GetTile(p_x + 1, p_y)->collision()) {
		ret.push_back(Vect2::RIGHT);
	}

	return ret;
}

int Level::NextIntersection(Vect2 & p_pos, const Vect2 & p_dir)
{
	Vect2 pos = p_pos.Round().CorrectTeleport();

	if (p_dir == Vect2::ZERO) {
		return -1;
	}

	int steps = 0;
	while (!IsIntersection((int)pos.x, (int)pos.y)) {
		pos += p_dir;
		pos = pos.CorrectTeleport();
		steps++;
	}

	p_pos = pos;

	return steps;
}

int Level::NextIntersection(Vect2 & p_pos, const Vect2 & p_dir, const std::vector<Vect2>& p_banned)
{
	Vect2 pos = p_pos.Round().CorrectTeleport();

	if (p_dir == Vect2::ZERO) {
		return -1;
	}

	int steps = 0;
	while (
		!GetTile((int)pos.x, (int)pos.y)->collision() &&
		!IsIntersection((int)pos.x, (int)pos.y) &&
		!IsBanned(p_pos, p_banned))
	{
		pos += p_dir;
		pos = pos.CorrectTeleport();
		steps++;
	}

	p_pos = pos;
	return steps;
}

bool Level::IsIntersection(int p_x, int p_y) const
{
	int x = CorrectTeleportAxis(p_x, Config::LEVEL_WIDTH);
	int y = CorrectTeleportAxis(p_y, Config::LEVEL_HEIGHT);

	bool diry = false;
	bool dirx = false;

	if (!m_tiles[CorrectTeleportAxis(y - 1, Config::LEVEL_HEIGHT)][x]->collision() ||
		!m_tiles[CorrectTeleportAxis(y + 1, Config::LEVEL_HEIGHT)][x]->collision())
	{
		diry = true;
	}
	if (!m_tiles[y][CorrectTeleportAxis(x - 1, Config::LEVEL_WIDTH)]->collision() ||
		!m_tiles[y][CorrectTeleportAxis(x + 1, Config::LEVEL_WIDTH)]->collision())
	{
		dirx = true;
	}

	return dirx && diry;
}

int Level::PelletsCount() const
{
	return m_pelletsCount + m_powerUps.size();
}

void Level::ResetAnimation()
{
	for (auto p : m_powerUps) {
		p->ResetAnimation();
	}
}

void Level::Update(float p_delta)
{
	for (auto p : m_powerUps) {
		p->Update(p_delta);
	}
}

void Level::Draw()
{
	m_drawManagerwPtr->Draw(m_levelSpritewPtr, 0, 24);

	DrawPellets(0, 24);

	for (auto p : m_powerUps) {
		p->Draw();
	}
}

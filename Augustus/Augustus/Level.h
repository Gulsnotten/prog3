#pragma once
#include <vector>
#include "Tile.h"

class DrawManager;
class Sprite;
class Vect2;
class PowerUp;
class ICollideable;

class Level
{
private:
	Tile charToTile(char c);

	DrawManager* m_drawManagerwPtr;
	Sprite* m_pelletSprite;
	Sprite* m_powerupSprite;
	Sprite* m_levelSpritewPtr;

	int m_pelletsCount;
	void DeletePowerUps();

	std::vector<std::vector<Tile>> m_tiles;
	std::vector<PowerUp*> m_powerUps;
public:
	Level();
	~Level();

	static const int WIDTH;
	static const int HEIGHT;
	static const float CENTER;
	static const float HOUSE_Y;
	static const float HOUSE_EXIT_Y;

	void LoadLevel();
	void DrawPellets(const int &p_x, const int &p_y);

	Tile GetTile(Vect2 p_vect2);
	void ReplaceTile(Vect2 p_vect2, Tile p_tile);
	bool PowerUpCollision(ICollideable* p_other);

	std::vector<Vect2> AvailableDirections(Vect2 p_pos);
	bool IsIntersection(Vect2 p_pos);
	int PelletsCount();

	void ResetAnimation();
	void Update(float p_delta);
	void Draw();
};


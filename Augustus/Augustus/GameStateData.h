#pragma once

#include "Ghost.h"
#include "Player.h"

class Level;
class Sprite;
struct GameObjectData;

class GameStateData
{
private:
	int m_score;
	DrawManager* m_drawManagerwPtr;

	void DeleteObjects();
	void DeleteLevel();
	void DeletePlayer();
	void DeleteGhosts();

	void CreateObjects();
	void CreateLevel();
	void CreatePlayer();
	void CreateGhosts();
	void AddGhost(IRoamingState* roaming, GameObjectData* p_data);
	GameObjectData* CreateGhostData(Vect2* p_pos);
public:
	GameStateData();
	~GameStateData();

	std::vector<Ghost*> m_ghosts;
	Player* m_player;
	Level* m_level;
	Sprite* m_levelSpritewPtr;
	

	void DrawAll(); // level, pellets, ghosts
	void DrawLevel();
	void DrawPellets();
	void DrawGhosts();
	void DrawPlayer();

	void Reset();
	void Retry();
	void Exit();
	
	void AddPoints(int p_points);
	int GetScore();
};
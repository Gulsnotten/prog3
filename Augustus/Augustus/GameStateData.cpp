#include "stdafx.h"
#include "GameStateData.h"

#include "MovementModule.h"
#include "Level.h"
#include "AmbushState.h"
#include "ChaseState.h"
#include "RandomBehaviorState.h"
#include "RoamAtRandom_State.h"
#include "Config.h"
#include "ServiceLocator.h"
#include "SpriteManager.h"
#include "DrawManager.h"

void GameStateData::DeleteObjects()
{
	DeleteGhosts();
	DeletePlayer();
	DeleteLevel();
}

void GameStateData::DeleteLevel()
{
	if (m_level != nullptr) {
		delete m_level;
		m_level = nullptr;
	}
}

void GameStateData::DeletePlayer()
{
	if (m_player != nullptr) {
		delete m_player;
		m_player = nullptr;
	}
}

void GameStateData::DeleteGhosts()
{
	for (auto g : m_ghosts) {
		delete g;
		g = nullptr;
	}
	m_ghosts.clear();
}

void GameStateData::CreateObjects()
{
	CreateLevel(); // do this first, pathfinding is coupled with it :I

	CreatePlayer();

	CreateGhosts();

	//m_player->AddObserver(this); //TODO: fix this
}

void GameStateData::CreateLevel()
{
	m_level = new Level();
	m_level->LoadLevel();
}

void GameStateData::CreatePlayer()
{
	Vect2* player_pos = new Vect2(Level::CENTER, 23.0f);
	m_player = new Player(
		new GameObjectData(
			player_pos,
			new MovementModule(m_level, player_pos),
			m_level
		));
}

void GameStateData::CreateGhosts()
{
	GameObjectData* data = nullptr;

	//red chaser
	data = CreateGhostData(new Vect2(Level::CENTER, Level::HOUSE_EXIT_Y));
	AddGhost(new ChaseState(data, m_player->GetPos()), data);

	//pink ambusher
	data = CreateGhostData(new Vect2(Level::CENTER, Level::HOUSE_Y));
	AddGhost(new AmbushState(data, m_player), data);

	//oblivious
	data = CreateGhostData(new Vect2(Level::CENTER - 2, Level::HOUSE_Y));
	AddGhost(new RandomBehaviorState(
		new AmbushState(data, m_player),
		new ChaseState(data, m_player->GetPos()),
		new RoamAtRandom_State(data)),
		data);

	//random boi
	data = CreateGhostData(new Vect2(Level::CENTER + 2, Level::HOUSE_Y));
	AddGhost(new RoamAtRandom_State(data), data);

	for (unsigned int i = 1; i < m_ghosts.size(); i++) {
		m_ghosts[i]->StartWaiting(i * Config::SPAWN_TIME);
	}

	SpriteManager* spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManagerwPtr = ServiceLocator<DrawManager>::GetService();
	m_levelSpritewPtr = spriteManager->CreateSprite("../Assets/level.png", 0, 0, 224, 248);
}

void GameStateData::AddGhost(IRoamingState * roaming, GameObjectData * p_data)
{
	Ghost* ghost = new Ghost(
		p_data,
		roaming,
		m_player->GetPos(),
		m_ghosts.size()
	);

	m_ghosts.push_back(ghost);
}

GameObjectData * GameStateData::CreateGhostData(Vect2 * p_pos)
{
	return new GameObjectData(
		p_pos,
		new MovementModule(m_level, p_pos),
		m_level
	);
}

GameStateData::GameStateData()
{
	m_score = 0;
}

GameStateData::~GameStateData()
{
	DeleteObjects();
}

void GameStateData::DrawAll()
{
	DrawLevel();
	DrawPellets();
	DrawGhosts();
	DrawPlayer();
}

void GameStateData::DrawLevel()
{
	m_drawManagerwPtr->Draw(m_levelSpritewPtr, 0, 24);
}

void GameStateData::DrawPellets()
{
	m_level->DrawPellets(0, 24);
}

void GameStateData::DrawGhosts()
{
	for (auto g : m_ghosts)
		g->Draw();
}

void GameStateData::DrawPlayer()
{
	m_player->Draw();
}

void GameStateData::Reset()
{
	DeleteObjects();
	CreateObjects();
}

void GameStateData::Retry()
{
	DeleteGhosts();
	DeletePlayer();

	CreatePlayer();
	CreateGhosts();
}

void GameStateData::Exit()
{
	DeleteObjects();
}

void GameStateData::AddPoints(int p_points)
{
	m_score += p_points;
}

int GameStateData::GetScore()
{
	return m_score;
}
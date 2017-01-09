#pragma once

#include "IState.h"

class Sprite;
class TestPlayerObject;
class TestEnemyObject;
class DrawManager;

class TestConcreteState : public IState
{
public:
	Sprite* blue = nullptr;
	Sprite* red = nullptr;
	Sprite* green = nullptr;
	Sprite* yellow = nullptr;
	TestPlayerObject* player = nullptr;
	TestEnemyObject* enemy = nullptr;
	DrawManager* drawmanager = nullptr;
	Mix_Chunk* sound = nullptr;
	void Enter();
	bool Update(float p_delta);
	void Exit();
	void Draw();
};
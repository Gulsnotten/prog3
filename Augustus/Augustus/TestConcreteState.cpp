#include "stdafx.h"
#include "TestConcreteState.h"
#include "ServiceLocator.h"
#include "TestEnemyObject.h"
#include "TestPlayerObject.h"
#include "CollisionManager.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include <iostream>
#include <memory>

void TestConcreteState::Enter()
{
	SpriteManager* spriteManager = ServiceLocator<SpriteManager>::GetService();
	drawmanager = ServiceLocator<DrawManager>::GetService();
	red = spriteManager->CreateSprite("../Assets/Test.bmp", 0, 0, 128, 128);
	green = spriteManager->CreateSprite("../Assets/Test.bmp", 128, 0, 128, 128);
	yellow = spriteManager->CreateSprite("../Assets/Test.bmp", 0, 128, 128, 128);
	blue = spriteManager->CreateSprite("../Assets/Test.bmp", 128, 128, 128, 128);
	player = new TestPlayerObject();
	enemy = new TestEnemyObject();
	sound = Mix_LoadWAV("../Assets/plopp.ogg");
}

bool TestConcreteState::Update(float p_delta)
{
	player->Update(p_delta);

	return false;
}

void TestConcreteState::Exit()
{
}

void TestConcreteState::Draw()
{
	player->Draw();
	drawmanager->SetDrawColor(100, 100, 100, 255);
	drawmanager->Draw(red, 150, 150);
	drawmanager->Draw(green, 300, 150);
	drawmanager->Draw(blue, 150, 300);
	drawmanager->Draw(yellow, 300, 300);

	
	if (CollisionManager::CheckCollision(player, enemy))
	{
		std::cout << "Collision" << std::endl;

		Mix_PlayChannel(-1, sound, 0);
		drawmanager->DebugDraw(player->m_collider->m_rect, 255, 0, 0, 0);
		drawmanager->DebugDraw(enemy->m_collider->m_rect, 255, 0, 0, 0);
	}
	else
	{
		drawmanager->DebugDraw(player->m_collider->m_rect, 0, 255, 0, 0);
		drawmanager->DebugDraw(enemy->m_collider->m_rect, 0, 255, 0, 0);
	}
}

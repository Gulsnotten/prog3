#include "stdafx.h"
#include "TestPlayerObject.h"

#include "ServiceLocator.h"
#include "InputManager.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "TestEnemyObject.h"
#include <iostream>


TestPlayerObject::TestPlayerObject()
{
	m_inputManager = ServiceLocator<InputManager>::GetService();
	m_sprite = m_spriteManager->CreateSprite("../Assets/EvilDuck.png", 0, 0, 128, 128);

	m_collider->m_rect.w = 64;
	m_collider->m_rect.h = 64;
	m_x = 100;
	m_y = 100;
	m_type = "Player";
}

TestPlayerObject::~TestPlayerObject()
{
}

void TestPlayerObject::Update(float p_delta)

{
	if (m_inputManager->IsKeyDown(SDL_SCANCODE_A))
	{
		m_x -= static_cast<int>(m_speed * p_delta);
	}
	if (m_inputManager->IsKeyDown(SDL_SCANCODE_D))
	{
		m_x += static_cast<int>(m_speed * p_delta);
	}
	if (m_inputManager->IsKeyDown(SDL_SCANCODE_W))
	{
		m_y -= static_cast<int>(m_speed * p_delta);
	}
	if (m_inputManager->IsKeyDown(SDL_SCANCODE_S))
	{
		m_y += static_cast<int>(m_speed * p_delta);
	}
	if (m_inputManager->IsMouseButtonPressed(0))
	{
		m_speed *= 2;
	}
	if (m_inputManager->IsMouseButtonReleased(0))
	{
		m_speed /= 2;
	}
	m_collider->m_rect.x = m_x + 34;
	m_collider->m_rect.y = m_y + 64;
}
void TestPlayerObject::Draw()
{
	m_drawManager->Draw(m_sprite, m_x, m_y);
}
void TestPlayerObject::OnCollision(ICollideable * p_other)
{
	IEntity* ent = dynamic_cast<IEntity*>(p_other);
	if (ent->GetType() == "Enemy")
	{
		TestEnemyObject* enemy = dynamic_cast<TestEnemyObject*>(ent);

		std::cout << "Player loses " << enemy->GetDamage() << " amount of HP." << std::endl;
	}

};

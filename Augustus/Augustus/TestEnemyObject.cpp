#include "stdafx.h"
#include "TestEnemyObject.h"

TestEnemyObject::TestEnemyObject()
{
	m_type = "Enemy";
	m_collider->m_rect.x = 300;
	m_collider->m_rect.y = 0;
	m_collider->m_rect.w = 50;
	m_collider->m_rect.h = 50;
}

TestEnemyObject::~TestEnemyObject()
{
}

void TestEnemyObject::Update(float p_delta)
{
}

void TestEnemyObject::OnCollision(ICollideable * p_other)
{
}

int TestEnemyObject::GetDamage()
{
	return 10;
}

#pragma once

#include "IEntity.h"
#include "ICollideable.h"

class TestEnemyObject : public IEntity, public ICollideable
{
public:
	TestEnemyObject();
	~TestEnemyObject();
	void Update(float p_delta);
	void OnCollision(ICollideable* p_other);
	int GetDamage();
};
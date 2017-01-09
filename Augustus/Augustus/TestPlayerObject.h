#pragma once

#include "IEntity.h"
#include "IDrawable.h"
#include "ICollideable.h"

class InputManager;

class TestPlayerObject : public IEntity, public IDrawable, public ICollideable
{
public:
	TestPlayerObject();
	virtual ~TestPlayerObject();
	void Update(float p_delta);
	void Draw();
	void OnCollision(ICollideable* p_other);
private:
	float m_speed = 150;
	InputManager* m_inputManager;
};
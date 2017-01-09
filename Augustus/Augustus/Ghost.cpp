#include "stdafx.h"
#include "Ghost.h"

#include "IState.h"
#include "vect2.h"

#include "ExitState.h"
#include "RunToHouse.h"
#include "WaitingState.h"

#include "ServiceLocator.h"
#include "GhostAnimations.h"
#include "AnimationController.h"
#include "FleeingState.h"
#include "IRoamingState.h"
#include "MovementModule.h"

#include "Config.h"

void Ghost::SwitchState(IState * p_state)
{
	if (m_currentStatewPtr != nullptr)
		m_currentStatewPtr->Exit();
	m_currentStatewPtr = p_state;
	m_currentStatewPtr->Enter();
}

void Ghost::SetAnimation()
{
	// get dir
	Vect2 dir = m_data->m_movement->GetDirection();
	
	if (m_currentStatewPtr == m_waiting) {
		dir = m_waiting->GetDirection();
	}
	if (m_currentStatewPtr == m_exitHouse) {
		dir = m_exitHouse->GetDirection();
	}

	if (dir == Vect2::ZERO) {
		dir = Vect2::UP;
	}

	// get animation
	Animation* animation = nullptr;

	if (m_currentStatewPtr == m_runToHouse) {
		animation = m_animationswPtr->GetDeathAnimation(dir);
	}
	else if (
		m_currentStatewPtr == m_roaming ||
		m_currentStatewPtr == m_exitHouse ||
		m_currentStatewPtr == m_waiting
		)
	{
		animation = m_animationswPtr->GetAnimation(dir, m_color);
	}
	else if (m_currentStatewPtr == m_fleeing) {
		if (m_fleeing->IsWarning()) {
			animation = m_animationswPtr->WarningAnimation;
		}
		else {
			animation = m_animationswPtr->BlueAnimation;
		}
	}

	if (animation != nullptr) {
		m_animation->SetAnimation(animation);
	}
}

Ghost::Ghost(GameObjectData * p_data, IRoamingState * p_roaming, Vect2 * p_playerPos, int p_color)
	: GameObject(p_data, Vect2(float(Config::TILE_SIZE), float(Config::TILE_SIZE)))
{
	m_color = p_color;

	m_roaming = p_roaming;
	m_fleeing = new FleeingState(p_data);
	m_waiting = new WaitingState(p_data);
	m_runToHouse = new RunToHouseState(p_data);
	m_exitHouse = new ExitState(p_data);

	SwitchState(m_roaming);
	m_roaming->OnSpawn();

	m_animationswPtr = ServiceLocator<GhostAnimations>::GetService();
	m_animation->SetAnimation(m_animationswPtr->GetAnimation(Vect2::UP, m_color));
}

Ghost::~Ghost()
{
	GameObject::~GameObject();

	delete m_waiting;
	delete m_exitHouse;
	delete m_roaming;
	delete m_fleeing;
	delete m_runToHouse;
}

bool Ghost::Update(float p_delta)
{
	GameObject::Update(p_delta);

	bool ret = m_currentStatewPtr->Update(p_delta);

	SetAnimation();

	if (!ret) {
		if (m_currentStatewPtr == m_runToHouse ||
			m_currentStatewPtr == m_waiting)
		{
			SwitchState(m_exitHouse);
		}
		else if (m_currentStatewPtr == m_exitHouse) {
			SwitchState(m_roaming);
			m_roaming->OnSpawn();
		}
		else if (m_currentStatewPtr == m_fleeing) {
			SwitchState(m_roaming);
		}
	}

	return false;
}

void Ghost::StartRoaming()
{
}

void Ghost::StartWaiting(int p_wait)
{
	SwitchState(m_waiting);
	m_waiting->Initialize(p_wait);
}

void Ghost::Flee()
{
	if (m_currentStatewPtr == m_fleeing ||
		m_currentStatewPtr == m_roaming)
	{
		SwitchState(m_fleeing);
	}
}

void Ghost::RunToHouse()
{
	SwitchState(m_runToHouse);
}

bool Ghost::IsFleeing()
{
	return (m_currentStatewPtr == m_fleeing);
}

bool Ghost::IsDead()
{
	return (m_currentStatewPtr == m_runToHouse);
}

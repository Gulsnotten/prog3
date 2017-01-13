#include "stdafx.h"
#include "Player.h"


#include "Sprite.h"
#include "vect2.h"
#include "DrawManager.h"
#include "MovementModule.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "spriteManager.h"
#include "AnimationController.h"
#include "Animation.h"
#include "PlayerAnimations.h"

#include "SoundManager.h"
#include "Level.h"

 
#include "CollisionManager.h"
#include "PowerUp.h"

void Player::UpdateInput()
{
	Vect2 dir = Vect2::ZERO;
	if (m_inputwPtr->IsKeyDown(SDL_SCANCODE_UP))
		dir = Vect2::UP;
	if (m_inputwPtr->IsKeyDown(SDL_SCANCODE_DOWN))
		dir = Vect2::DOWN;
	if (m_inputwPtr->IsKeyDown(SDL_SCANCODE_LEFT))
		dir = Vect2::LEFT;
	if (m_inputwPtr->IsKeyDown(SDL_SCANCODE_RIGHT))
		dir = Vect2::RIGHT;

	if (dir != Vect2::ZERO)
		m_inputBuffer = dir;
}


Player::Player(GameObjectData * p_data)
	: GameObject(p_data, Vect2(float(Config::TILE_SIZE), float(Config::TILE_SIZE))),
	m_inputBuffer(Vect2::ZERO), m_isDead(false)
{
	m_data = p_data;

 	m_inputwPtr = ServiceLocator<InputManager>::GetService();

	m_animationswPtr = ServiceLocator<PlayerAnimations>::GetService();
	m_animation->SetAnimation(m_animationswPtr->Still);

	SoundManager* soundManager = ServiceLocator<SoundManager>::GetService();
}

Player::~Player()
{
	GameObject::~GameObject();
}

bool Player::Update(float p_delta)
{
	GameObject::Update(p_delta);

	UpdateInput();

	bool bumped = m_data->m_movement->Update(p_delta, m_inputBuffer, float(Config::MOVEMENT_SPEED));

	Vect2 currentdir = m_data->m_movement->GetDirection();
	Animation* next_animation = nullptr;

	if (currentdir == Vect2::ZERO) {
		next_animation = m_animationswPtr->Still;
	}
	else if (bumped) {
		next_animation = m_animationswPtr->GetStoppedAnimation(currentdir);
	}
	else {
		next_animation = m_animationswPtr->GetAnimation(currentdir);
	}
	m_animation->SetAnimation(next_animation);

	return bumped;
}

bool Player::SteppedOnTile()
{
	return m_data->m_movement->SteppedOnTile();
}

void Player::Kill()
{
	m_isDead = true;
}

bool Player::IsDead()
{
	return m_isDead;
}

Vect2 Player::GetDirection()
{
	return m_data->m_movement->GetDirection();
}

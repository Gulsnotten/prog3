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

#include "Config.h"

void Player::UpdateSound(bool p_bumped)
{
	if (p_bumped) {
		m_soundwPtr->Stop();
	}
	else {
		Vect2 pos = m_data->m_pos->Round();
		Level* level = m_data->m_levelwPtr;

		TileType tile = level->GetTile(pos).GetType();

		if (tile == TileType::Pellet ||
			tile == TileType::Powerup)
		{
			if (tile == TileType::Powerup) {
				NotifyObservers(Config::POWER_UP_MSG);
			}

			if (!m_soundwPtr->IsPlaying()) {
				m_soundwPtr->PlayLooped();
			}

			level->ReplaceTile(pos, Tile(TileType::Empty));
		}
		else
		{
			m_soundwPtr->Stop();
		}
	}
}

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
	m_soundwPtr = soundManager->CreateSound("../Assets/sound/waka.wav");
}

Player::~Player()
{
	GameObject::~GameObject();

	m_soundwPtr->Stop();
}

bool Player::Update(float p_delta)
{
	GameObject::Update(p_delta);

	UpdateInput();

	bool bumped = m_data->m_movement->Update(p_delta, m_inputBuffer, float(Config::MOVEMENT_SPEED));

	if (m_data->m_movement->SteppedOnTile()){
		UpdateSound(bumped);
	}

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

	return false;
}

void Player::Kill()
{
	m_isDead = true;
	m_soundwPtr->Stop();
}

void Player::StopSound()
{
	m_soundwPtr->Stop();
}

bool Player::IsDead()
{
	return m_isDead;
}

Vect2 Player::GetDirection()
{
	return m_data->m_movement->GetDirection();
}

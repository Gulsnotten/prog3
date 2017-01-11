#include "stdafx.h"
#include "PowerUp.h"
#include "Config.h"

#include "Animation.h"
#include "ServiceLocator.h"
#include "SpriteManager.h"
#include <string>

PowerUp::PowerUp(Vect2 p_pos)
	: ICollideable(), IAnimationAble()
{
	m_pos = p_pos;

	m_collider->m_rect.x = int(p_pos.x);
	m_collider->m_rect.y = int(p_pos.y);
	m_collider->m_rect.w = Config::TILE_SIZE;
	m_collider->m_rect.h = Config::TILE_SIZE;


	SpriteManager* spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_flashAnimation = new Animation();
	std::string file = "../Assets/pellet.png";

	for (int x = 1; x < 3; x++) {
		m_flashAnimation->AddFrame(AnimationFrame(
			spriteManager->CreateSprite(file, x * Config::TILE_SIZE, 0, Config::TILE_SIZE, Config::TILE_SIZE),
			Config::ANIMATION_SPEED_POWER_UP
		));
	}

	m_animation->SetAnimation(m_flashAnimation);
}

PowerUp::~PowerUp()
{
	delete m_flashAnimation;
}

void PowerUp::Update(float p_delta)
{
	m_animation->Update(p_delta);
}

void PowerUp::Draw()
{
	m_animation->Draw(m_pos);
}

void PowerUp::ResetAnimation()
{
	m_animation->ResetAnimation();
}

#include "stdafx.h"
#include "FruitAnimations.h"

#include "Animation.h"
#include "ServiceLocator.h"
#include "Spritemanager.h"

 

FruitAnimations::FruitAnimations()
{
	SpriteManager* spriteManager = ServiceLocator<SpriteManager>::GetService();
	std::string file = "../Assets/fruits.png";

	Animation* empty = new Animation();
	int size = 16;
	int flash_time = int(Config::TEXT_FLASH_SPEED * 1000);

	for (unsigned int x = 0; x < 3; x++) {
		for (unsigned int y = 0; y < 3; y++) {
			Animation* animation = new Animation();
			Sprite* sprite = spriteManager->CreateSprite(file, x * size, y * size, size, size);

			m_sprites.push_back(sprite);
			animation->AddFrame(AnimationFrame(sprite, flash_time));
			m_still.push_back(animation);
		}
	}

	for (unsigned int i = 0; i < 8; i++) {
		Animation* animation = new Animation();

		animation->AddFrame(AnimationFrame(m_sprites.back(), flash_time));
		animation->AddFrame(AnimationFrame(m_sprites[i], flash_time));

		m_flash.push_back(animation);
	}


	file = "../Assets/fruit_scores.png";
	size = 20;

	for (unsigned int x = 0; x < 3; x++) {
		for (unsigned int y = 0; y < 3; y++) {
			Animation* animation = new Animation();
			Sprite* sprite = spriteManager->CreateSprite(file, x * size, y * size, size, size);

			animation->AddFrame(AnimationFrame(sprite, 1000));
			m_scores.push_back(animation);
		}
	}
}

FruitAnimations::~FruitAnimations()
{
	for (auto a : m_still) {
		delete a;
	}
	for (auto a : m_flash) {
		delete a;
	}
}

Animation * FruitAnimations::GetAnimation(int p_index)
{
	return m_still[p_index];
}

Animation * FruitAnimations::GetFlashAnimation(int p_index)
{
	return m_flash[p_index];
}

Animation * FruitAnimations::GetScoreAnimation(int p_index)
{
	return m_scores[p_index];
}

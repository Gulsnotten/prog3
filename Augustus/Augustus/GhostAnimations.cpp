#include "stdafx.h"
#include "GhostAnimations.h"

#include "SpriteManager.h"
#include "Sprite.h"
#include "ServiceLocator.h"
#include <string>

#include "Config.h"


GhostAnimations::GhostAnimations()
{
	SpriteManager* spriteManager = ServiceLocator<SpriteManager>::GetService();
	std::string file = "../Assets/ghost.png";

	int speed = Config::ANIMATION_SPEED_GHOST; // length of each frame

	m_colorAnimations.clear();
	for (int y = 0; y < 4; y++) {
		DirectionCollection collection;

		for (int d = 0; d < 4; d++) {

			Animation* ptr = collection.GetDirFromInt(d);

			for (int c = 0; c < 2; c++) {
				ptr->AddFrame(AnimationFrame(
					spriteManager->CreateSprite(file, ((d * 2) + c) * 16, y * 16, 16, 16),
					speed
				));
			}
		}

		m_colorAnimations.push_back(collection);
	}

	for (int i = 0; i < 4; i++) {
		Animation* ptr = m_deathCollection.GetDirFromInt(i);

		ptr->AddFrame(AnimationFrame(
				spriteManager->CreateSprite(file, (4 + i) * 16, 4 * 16, 16, 16),
				1000
			));
	}

	WarningAnimation = new Animation();
	
	for (int i = 0; i < 2; i++) {
		WarningAnimation->AddFrame(AnimationFrame(
			spriteManager->CreateSprite(file, (2 + i) * 16, 4 * 16, 16, 16),
			speed
		));
	}

	BlueAnimation = new Animation();
	for (int i = 0; i < 2; i++) {
		AnimationFrame next_frame = AnimationFrame(
			spriteManager->CreateSprite(file, i * 16, 4 * 16, 16, 16),
			speed
		);

		BlueAnimation->AddFrame(next_frame);
		WarningAnimation->AddFrame(next_frame);
	}
}


GhostAnimations::~GhostAnimations()
{
	m_deathCollection.DeletePointers();

	for (auto c : m_colorAnimations){
		c.DeletePointers();
	}

	delete BlueAnimation;
	delete WarningAnimation;
}

Animation * GhostAnimations::GetAnimation(Vect2 p_dir, int p_index)
{
	return m_colorAnimations[p_index].GetDirFromVect(p_dir);
}

Animation * GhostAnimations::GetDeathAnimation(Vect2 p_dir)
{
	return m_deathCollection.GetDirFromVect(p_dir);
}
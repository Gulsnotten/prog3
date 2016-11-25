#include "stdafx.h"
#include "SpriteManager.h"
#include "DrawManager.h"


SpriteManager::SpriteManager()
{
}


SpriteManager::~SpriteManager()
{
}

Sprite * SpriteManager::CreateSprite(const std::string p_file, unsigned int p_x, unsigned int p_y, unsigned int p_w, unsigned int p_h)
{
	auto it = m_textures.find(p_file); // returns an iterator to a pos or end, depending on success
	if (it == m_textures.end()) { // it hasn't found the texture!

	}

	//TODO: find texture in map, if not load texture
	//		create a new sprite from the texture, insert sprite into vector
	//		return sprite
	return nullptr;
}

void SpriteManager::DestroySprite(Sprite * p_sprite)
{
	//TODO: iterate over the vector to find the specific sprite, if found, delete
}

#include "stdafx.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "DrawManager.h"

SpriteManager::SpriteManager()
{
}

SpriteManager::SpriteManager(SDL_Renderer * p_renderer)
{
	m_renderer = p_renderer;
}

SpriteManager::~SpriteManager()
{
	for (auto t : m_textures) {
		SDL_DestroyTexture(t.second);
		t.second = nullptr;
	}

	for (auto s : m_sprites) {
		delete s;
		s = nullptr;
	}
}

Sprite * SpriteManager::CreateSprite(const std::string p_file, unsigned int p_x, unsigned int p_y,
										unsigned int p_w, unsigned int p_h)
{
	auto it = m_textures.find(p_file); // Returns an iterator to a pos or end, depending on success
	if (it == m_textures.end())
	{
		// If we do not find the texture we need to load it and inser it in to our std::map so
		// that we may create pointers to the same texture for several sprites.
		SDL_Surface* xSurface = IMG_Load(p_file.c_str());
		SDL_Texture* xTexture = SDL_CreateTextureFromSurface(m_renderer, xSurface);
		SDL_FreeSurface(xSurface);
		m_textures.insert(std::pair<std::string, SDL_Texture*>(p_file, xTexture));
		it = m_textures.find(p_file);
	}

	Sprite* xSprite = new Sprite(it->second, p_x, p_y, p_w, p_h);
	// if the sprite was already stored in the vector, return it
	// this way we can reuse the same data
	for (auto s : m_sprites) {
		if (*s == *xSprite) {
			delete xSprite;
			return s;
		}
	}

	m_sprites.push_back(xSprite);
	return xSprite;
}

void SpriteManager::DestroySprite(Sprite * p_sprite)
{
	//TODO: iterate over the vector to find the specific sprite, if found, delete
}

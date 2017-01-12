#include "stdafx.h"
#include "DrawManager.h"
#include "Sprite.h"

#include "Config.h"

// credit to Leo Jansson for the scaling in DrawManager::Draw(Sprite* p_sprite, int p_x, int p_y)

DrawManager::DrawManager()
{
}

DrawManager::~DrawManager()
{
}

void DrawManager::Initialize()
{
	m_window = SDL_CreateWindow("Augustus", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		Config::WINDOW_WIDTH * Config::WINDOW_SCALE,
		Config::WINDOW_HEIGHT * Config::WINDOW_SCALE,
		0);
	assert(m_window != nullptr && "SDL_CreateWindow Failed");

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_VIDEO_OPENGL);
	assert(m_renderer != nullptr && "SDL_CreateRenderer Failed");

}

void DrawManager::Shutdown()
{
	SDL_DestroyWindow(m_window);
	m_window = nullptr;

	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
}

void DrawManager::Clear()
{
	SDL_RenderClear(m_renderer);
}

void DrawManager::SetDrawColor(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{
	SDL_SetRenderDrawColor(m_renderer, p_r, p_g, p_b, p_a);
}
void DrawManager::Present()
{
	SDL_RenderPresent(m_renderer);
}

void DrawManager::Draw(Sprite* p_sprite, int p_x, int p_y)
{
	// credit to Leo Jansson for the scaling
	SDL_Rect dstRect = {
		p_x * Config::WINDOW_SCALE,
		p_y * Config::WINDOW_SCALE,
		p_sprite->GetSource().w * Config::WINDOW_SCALE,
		p_sprite->GetSource().h * Config::WINDOW_SCALE
	};
	SDL_RenderCopy(m_renderer, p_sprite->GetTexture(), &p_sprite->GetSource(), &dstRect);
}

void DrawManager::Draw(Sprite * p_sprite, float p_x, float p_y)
{
	// credit to Leo Jansson for the scaling
	SDL_Rect dstRect = {
		int(p_x * Config::WINDOW_SCALE),
		int(p_y * Config::WINDOW_SCALE),
		p_sprite->GetSource().w * Config::WINDOW_SCALE,
		p_sprite->GetSource().h * Config::WINDOW_SCALE
	};
	SDL_RenderCopy(m_renderer, p_sprite->GetTexture(), &p_sprite->GetSource(), &dstRect);
}

void DrawManager::Draw(Sprite * p_sprite, int p_x, int p_y, Uint8 p_r, Uint8 p_g, Uint8 p_b)
{
	SDL_SetTextureColorMod(p_sprite->GetTexture(), p_r, p_g, p_b);

	Draw(p_sprite, p_x, p_y);

	SDL_SetTextureColorMod(p_sprite->GetTexture(), 255, 255, 255);
}

void DrawManager::Draw(Sprite * p_sprite, int p_x, int p_y, SDL_Color p_color)
{
	Draw(p_sprite, p_x, p_y,
		p_color.r,
		p_color.g,
		p_color.b
	);
}

void DrawManager::DebugDraw(int p_x, int p_y, int p_w, int p_h)
{
	SDL_Rect rect = { p_x,p_y,p_w,p_h };
	SDL_RenderDrawRect(m_renderer, &rect);
}

void DrawManager::DebugDraw(SDL_Rect &p_rect)
{
	
}

void DrawManager::DebugDraw(SDL_Rect & p_rect, Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{
	SaveDrawColor();
	SetDrawColor(p_r, p_g, p_b, p_a);
	SDL_RenderDrawRect(m_renderer, &p_rect);
	LoadDrawColor();
}

SDL_Renderer * DrawManager::GetRenderer()
{
	return m_renderer;
}

void DrawManager::SaveDrawColor()
{
	SDL_GetRenderDrawColor(m_renderer, &m_r, &m_g, &m_b, &m_a);
}

void DrawManager::LoadDrawColor()
{
	SDL_SetRenderDrawColor(m_renderer, m_r, m_g, m_b, m_a);
}

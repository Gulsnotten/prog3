#include "stdafx.h"
#include "DrawManager.h"


DrawManager::DrawManager()
{
}


DrawManager::~DrawManager()
{
}

void DrawManager::Initialize()
{
	m_window = SDL_CreateWindow("Augustus", SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	assert(m_window != nullptr);

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_VIDEO_OPENGL);
	assert(m_renderer != nullptr);
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

void DrawManager::Draw(Sprite & p_sprite, int p_x, int p_y)
{
	// TODO: will use sprite and sprites txture + rect to draw
}

void DrawManager::DebugDraw(int p_x, int p_y, int p_w, int p_h)
{
	SDL_Rect rect = { p_x, p_y, p_w, p_h };
	SDL_RenderDrawRect(m_renderer, &rect);
}

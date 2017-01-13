#include "stdafx.h"
#include "DrawManager.h"
#include "Sprite.h"

#include <iostream>

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
		SDL_WINDOW_RESIZABLE);
	assert(m_window != nullptr && "SDL_CreateWindow Failed");

	// frame rate was capping, so I changed the flag according to this page
	// http://stackoverflow.com/questions/21949479/is-there-a-frame-rate-cap-built-into-sdl-2-0

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	assert(m_renderer != nullptr && "SDL_CreateRenderer Failed");

	UpdateWindowSize();
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
	SDL_RenderCopy(m_renderer, p_sprite->GetTexture(), &p_sprite->GetSource(), &GetDrawRect(p_sprite, (float)p_x, (float)p_y));
}

void DrawManager::Draw(Sprite * p_sprite, float p_x, float p_y)
{
	
	SDL_RenderCopy(m_renderer, p_sprite->GetTexture(), &p_sprite->GetSource(), &GetDrawRect(p_sprite, p_x, p_y));
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

SDL_Rect DrawManager::GetDrawRect(Sprite * p_sprite, float p_x, float p_y)
{
	SDL_Rect dstRect = {
		(int)round(p_x * m_scale),
		(int)round(p_y * m_scale),
		(int)round(p_sprite->GetSource().w * m_scale),
		(int)round(p_sprite->GetSource().h * m_scale)
	};
	return dstRect;
}

void DrawManager::UpdateWindowSize()
{
	// credit to Leo Jansson for the scaling,
	// though at this point I'm not really using
	// the WINDOW_SCALE variable when drawing

	int w;
	int h;
	int x;
	int y;
	SDL_GetWindowSize(m_window, &w, &h);
	SDL_GetWindowPosition(m_window, &x, &y);
	int start_w = w;
	int start_h = h;
	float aspect = (float)Config::WINDOW_WIDTH / Config::WINDOW_HEIGHT;

	if (w / (float)Config::WINDOW_WIDTH > h / (float)Config::WINDOW_HEIGHT) { // if window is wide
		m_scale = (float)h / Config::WINDOW_HEIGHT;
		w = int(h * aspect);
	}
	else {
		m_scale = (float)w / Config::WINDOW_WIDTH;
		h = int(w / aspect);
	}

	if (w != start_w) {
		x += (start_w - w) / 2;
	}
	else {
		y += (start_h - h) / 2;
	}
	SDL_SetWindowSize(m_window, w, h);
	SDL_SetWindowPosition(m_window, x, y);

	std::cout << "Changed window size\n";
}

void DrawManager::SaveDrawColor()
{
	SDL_GetRenderDrawColor(m_renderer, &m_r, &m_g, &m_b, &m_a);
}

void DrawManager::LoadDrawColor()
{
	SDL_SetRenderDrawColor(m_renderer, m_r, m_g, m_b, m_a);
}

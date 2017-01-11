#pragma once

class Sprite;

class DrawManager
{
public:
	DrawManager();
	~DrawManager();
	void Initialize(); // Create window + renderer
	void Shutdown();   // delete window + renderer
	void Clear();
	void SetDrawColor(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a);      // use sdl functionality to clear
	void Present();    //         -||-          to present
	void Draw(Sprite* p_sprite, int p_x, int p_y); // -||- to rendercopy
	void Draw(Sprite* p_sprite, int p_x, int p_y, Uint8 p_r, Uint8 p_g, Uint8 p_b);
	void Draw(Sprite* p_sprite, int p_x, int p_y, SDL_Color p_color);
	void DebugDraw(int p_x, int p_y, int p_w, int p_h); // -||- to drawrect
	void DebugDraw(SDL_Rect &p_rect);
	void DebugDraw(SDL_Rect &p_rect, Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a);
	SDL_Renderer* GetRenderer();
private:
	void SaveDrawColor();
	void LoadDrawColor();
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	Uint8 m_r;
	Uint8 m_g;
	Uint8 m_b;
	Uint8 m_a;

};




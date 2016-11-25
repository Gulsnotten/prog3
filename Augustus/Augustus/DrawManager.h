#pragma once

class Sprite;

class DrawManager
{
public:
	DrawManager();
	~DrawManager();
	void Initialize(); // create window + renderer
	void Shutdown(); // delete window + renderer
	void Clear();
	void SetDrawColor(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a); // use sdl functionality to clear
	void Present(); // -||- to present
	void Draw(Sprite &p_sprite, int p_x, int p_y); // -||- to draw
	void DebugDraw(int p_x, int p_y, int p_w, int p_h);// -||- to rendercopy
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};


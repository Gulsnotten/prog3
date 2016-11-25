#pragma once
class Sprite
{
public:
	Sprite();
	Sprite(SDL_Texture* p_texture, int p_x, int p_y, int p_w, int p_h);
	~Sprite();
	void SetSource(int p_x, int p_y, int p_w, int p_h);
private:
	SDL_Texture* m_texture;
	SDL_Rect m_source; // Defines what rect of the sprite should be drawn
};


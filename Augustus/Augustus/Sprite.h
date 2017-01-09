#pragma once
class Sprite // deletion is handled in SpriteManager
{
public:
	Sprite(SDL_Texture* p_texture, int p_x, int p_y, int p_w, int p_h);
	~Sprite();
	void SetSource(int p_x, int p_y, int p_w, int p_h);
	SDL_Rect GetSource();
	SDL_Texture* GetTexture();

	bool Sprite::operator==(const Sprite& p_other);
	bool Sprite::operator!=(const Sprite& p_other);
private:
	Sprite();
	SDL_Texture* m_texture;
	SDL_Rect m_source; // Defines what part of the texture that should be drawn
};


#pragma once
#include <string>
#include <map>

class Sprite;
class Vect2;
class DrawManager;

class Font
{
private:
	DrawManager* m_drawManagerwPtr;

	std::map<char, Sprite*> m_characters;
	SDL_Color m_white;

	static const int SIZE;
public:
	Font();
	~Font();
	
	int GetLength(std::string p_string);
	void Draw(Vect2 p_pos, std::string p_string);
	void DrawCentered(Vect2 p_pos, std::string p_string);
	void DrawLeftAnchor(Vect2 p_pos, std::string p_string);

	void Draw(Vect2 p_pos, std::string p_string, SDL_Color p_color);
	void DrawCentered(Vect2 p_pos, std::string p_string, SDL_Color p_color);
	void DrawLeftAnchor(Vect2 p_pos, std::string p_string, SDL_Color p_color);
};
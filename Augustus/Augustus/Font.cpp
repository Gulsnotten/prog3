#include "stdafx.h"
#include "Font.h"

#include "vect2.h"

#include "ServiceLocator.h"
#include "SpriteManager.h"
#include "TextLoader.h"
#include "DrawManager.h"

const int Font::SIZE = 8;

Font::Font()
{
	SpriteManager* spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_drawManagerwPtr = ServiceLocator<DrawManager>::GetService();

	std::string file = "../Assets/font/NES_font.png";
	std::vector<std::string> rawChars = TextFileManipulator::LoadFile("../Assets/font/font.txt");

	m_characters.clear();

	int w = 16;
	int h = 6;

	// load shit
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			m_characters.insert(std::pair<char, Sprite*>(rawChars[y][x],
					spriteManager->CreateSprite(file, x * SIZE, y * SIZE, SIZE, SIZE)
				));
		}
	}

	m_white = SDL_Color();
	m_white.r = 255;
	m_white.g = 255;
	m_white.b = 255;
	m_white.a = 255;
}

Font::~Font()
{
}

int Font::GetLength(std::string p_string)
{
	return p_string.size() * SIZE; // TODO
}

void Font::Draw(Vect2 p_pos, std::string p_string)
{
	
	Draw(p_pos, p_string, m_white);
}

void Font::DrawCentered(Vect2 p_pos, std::string p_string)
{
	DrawCentered(p_pos, p_string, m_white);
}

void Font::DrawLeftAnchor(Vect2 p_pos, std::string p_string)
{
	DrawLeftAnchor(p_pos, p_string, m_white);
}

void Font::Draw(Vect2 p_pos, std::string p_string, SDL_Color p_color)
{
	Vect2 pos = p_pos;
	for (unsigned int x = 0; x < p_string.size(); x++) {
		auto it = m_characters.find(p_string[x]);

		if (it != m_characters.end()) {
			Sprite* charSprite = it->second;

			m_drawManagerwPtr->Draw(charSprite, (int)pos.x, (int)pos.y, p_color);
		}

		pos.x += SIZE;
	}
}

void Font::DrawCentered(Vect2 p_pos, std::string p_string, SDL_Color p_color)
{
	int length = GetLength(p_string);

	Vect2 pos = p_pos;
	pos.x -= (float)length / 2.0f;

	Draw(pos, p_string, p_color);
}

void Font::DrawLeftAnchor(Vect2 p_pos, std::string p_string, SDL_Color p_color)
{
	Vect2 pos = p_pos;

	int offset = GetLength(p_string);
	pos.x -= offset;

	Draw(pos, p_string, p_color);
}

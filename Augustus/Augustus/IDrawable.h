#pragma once

class Sprite;
class DrawManager;
class SpriteManager;

class IDrawable
{
public:
	IDrawable();
	virtual ~IDrawable();
	virtual void Draw() = 0;
protected:
	Sprite* m_sprite = nullptr;
	DrawManager* m_drawManager = nullptr;
	SpriteManager* m_spriteManager = nullptr;
};
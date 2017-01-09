#include "stdafx.h"
#include "IDrawable.h"
#include "ServiceLocator.h"

IDrawable::IDrawable()
{
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
}

IDrawable::~IDrawable()
{
	m_sprite = nullptr;
	m_drawManager = nullptr;
	m_spriteManager = nullptr;
}

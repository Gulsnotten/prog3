#include "stdafx.h"
#include "IAnimationAble.h"

#include "ServiceLocator.h"
#include "DrawManager.h"

#include "AnimationController.h"

IAnimationAble::IAnimationAble(AnimationController * p_animation)
	: m_animation(p_animation)
{
	m_drawManagerwPtr = ServiceLocator<DrawManager>::GetService();
}

IAnimationAble::~IAnimationAble()
{
	delete m_animation;
	m_animation = nullptr;
}
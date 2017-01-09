#include "stdafx.h"
#include "IGameState.h"

#include "ServiceLocator.h"
#include "DrawManager.h"

IGameState::IGameState(GameStateData * p_data)
	: m_datawPtr(p_data)
{
	m_drawManagerwPtr = ServiceLocator<DrawManager>::GetService();
}

IGameState::~IGameState()
{
}

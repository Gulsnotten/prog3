#include "stdafx.h"
#include "IState_PDA.h"

#include "ServiceLocator.h"
#include "DrawManager.h"

IState_PDA::IState_PDA()
{
	m_drawManagerwPtr = ServiceLocator<DrawManager>::GetService();
}


IState_PDA::~IState_PDA()
{
}

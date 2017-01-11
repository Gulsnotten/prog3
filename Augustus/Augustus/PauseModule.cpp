#include "stdafx.h"
#include "PauseModule.h"


PauseModule::PauseModule()
{
	m_time = 0;
}

PauseModule::~PauseModule()
{
}

bool PauseModule::Update(float p_delta)
{
	if (m_time > 0) {
		m_time -= p_delta;
		return true;
	}
	return false;
}

bool PauseModule::IsPaused()
{
	return m_time > 0;
}

void PauseModule::SetPause(float p_time)
{
	m_time = p_time;
}
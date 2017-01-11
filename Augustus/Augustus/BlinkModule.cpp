#include "stdafx.h"
#include "BlinkModule.h"

BlinkModule::BlinkModule(float p_time)
	: m_time(p_time)
{
	m_current = 0;
}

BlinkModule::~BlinkModule()
{
}

void BlinkModule::Update(float p_delta)
{
	m_current += p_delta;
	if (m_current > m_time * 2) {
		m_current -= m_time * 2;
	}
}

bool BlinkModule::IsShowing()
{
	return m_current > m_time;
}

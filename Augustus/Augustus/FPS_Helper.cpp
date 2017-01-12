#include "stdafx.h"
#include "FPS_Helper.h"

#include <iostream>
#include "Config.h"

int FPS_Helper::GetDeltaFps(float p_delta)
{
	return int(1.0f / p_delta);
}

void FPS_Helper::UpdateFPS(float p_delta)
{
	m_frames++;
	m_time += p_delta;
	if (m_time > 1.0f) {
		m_lastFPS = m_frames;

		m_time = 0;
		m_frames = 0;

		PrintFPS();
	}
}

void FPS_Helper::PrintFPS()
{
	std::cout << "FPS : " << m_lastFPS << "\n";
}

FPS_Helper::FPS_Helper()
{
	m_time = 0;
	m_lastFPS = 0;
}

FPS_Helper::~FPS_Helper()
{
}

void FPS_Helper::Update(float p_delta)
{
	UpdateFPS(p_delta);
}

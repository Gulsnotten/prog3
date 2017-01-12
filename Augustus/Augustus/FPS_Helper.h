#pragma once

class FPS_Helper
{
private:
	int m_frames;
	int m_lastFPS;
	float m_time;
	int GetDeltaFps(float p_delta);
	void UpdateFPS(float p_delta);
	void PrintFPS();
public:
	FPS_Helper();
	~FPS_Helper();
	void Update(float p_delta);
};
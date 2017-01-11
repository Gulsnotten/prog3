#pragma once
#include "Font.h"

class BlinkModule
{
private:
	float m_time;
	float m_current;
public:
	BlinkModule(float p_time);
	~BlinkModule();

	void Update(float p_delta);
	bool IsShowing();
};
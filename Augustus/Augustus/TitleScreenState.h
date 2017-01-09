#pragma once
#include "IState_PDA.h"

class Sprite;
class DrawManager;
class InputManager;

class TitleScreenState : public IState_PDA
{
private:
	Sprite* m_BG_Sprite;
	DrawManager* m_drawManager;
	InputManager* m_inputManager;
public:
	TitleScreenState();
	~TitleScreenState();

	void Enter();
	void Exit();
	PDA::PDA_ReturnFlag Update(float p_delta);
	IState_PDA* NextState();
};


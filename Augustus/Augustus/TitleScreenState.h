#pragma once
#include "IState_PDA.h"

class Sprite;
class DrawManager;
class InputManager;

class TitleScreenState : public IState_PDA
{
private:
	Sprite* m_BG_Sprite;
	InputManager* m_inputManager;
public:
	TitleScreenState();
	~TitleScreenState();

	void Enter();
	void Exit();
	PDA::PDA_ReturnFlag Update(float p_delta);
	void Draw();
	IState_PDA* NextState();
};


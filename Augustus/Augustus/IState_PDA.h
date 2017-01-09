#pragma once
#include "PDA.h"

class IState_PDA
{
public:
	IState_PDA();
	virtual ~IState_PDA();

	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual PDA::PDA_ReturnFlag Update(float p_delta) = 0;
	virtual IState_PDA* NextState() = 0;
};


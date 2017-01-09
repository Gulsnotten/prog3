#pragma once
#include "IState.h"
class IRoamingState :
	public IState
{
public:
	IRoamingState();
	virtual ~IRoamingState();

	virtual void OnSpawn();
};


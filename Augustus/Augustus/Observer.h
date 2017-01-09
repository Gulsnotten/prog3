#pragma once
#include <string>
class Observer
{
public:
	Observer();
	virtual ~Observer();

	virtual void Notify(std::string p_msg) = 0;
};


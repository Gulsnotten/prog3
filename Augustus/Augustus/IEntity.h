#pragma once

#include <string>

class IEntity
{
public:
	IEntity();
	~IEntity();
	virtual void Update(float p_delta) = 0;
	const std::string GetType();
protected:
	std::string m_type;
	int m_x;
	int m_y;
};

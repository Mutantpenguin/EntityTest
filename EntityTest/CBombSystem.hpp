#pragma once

#include "CComponentSystem.hpp"

#include "MyECS.hpp"

class CBombSystem : public CComponentSystem
{
public:
	CBombSystem( MyECS &ecs ) :
		m_ecs { ecs }
	{}

	~CBombSystem()
	{};

	virtual void Process();

private:
	MyECS &m_ecs;
};


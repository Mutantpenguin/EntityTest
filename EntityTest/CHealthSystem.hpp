#pragma once

#include "CComponentSystem.hpp"

#include "MyECS.hpp"

class CHealthSystem : public CComponentSystem
{
public:
	CHealthSystem( MyECS &ecs ) :
		m_ecs { ecs }
	{}

	~CHealthSystem()
	{};

	virtual void Process();

private:
	MyECS &m_ecs;
};


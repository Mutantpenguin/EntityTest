#pragma once

#include "CBaseSystem.hpp"

#include "MyECS.hpp"

class CHealthSystem : public CBaseSystem
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


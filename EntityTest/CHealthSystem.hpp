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

	virtual void Run();

private:
	MyECS &m_ecs;
};


#pragma once

#include "CBaseSystem.hpp"

#include "MyECS.hpp"

class CBombSystem : public CBaseSystem
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

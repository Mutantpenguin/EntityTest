#pragma once

#include "CBaseSystem.hpp"

#include "MyECS.hpp"

class CBoundingBoxSystem : public CBaseSystem
{
public:
	CBoundingBoxSystem( MyECS &ecs ) :
		m_ecs { ecs }
	{}

	~CBoundingBoxSystem()
	{};

	virtual void Process();

private:
	MyECS &m_ecs;
};


#pragma once

#include "CComponentSystem.hpp"

#include "MyECS.hpp"

class CBoundingBoxSystem : public CComponentSystem
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


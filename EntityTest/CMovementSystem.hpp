#pragma once

#include "CComponentSystem.hpp"

#include "MyECS.hpp"

class CMovementSystem : public CComponentSystem
{
public:
	CMovementSystem( MyECS &ecs ) :
		m_ecs { ecs }
	{}

	~CMovementSystem()
	{};

	virtual void Process();

private:
	MyECS &m_ecs;
};


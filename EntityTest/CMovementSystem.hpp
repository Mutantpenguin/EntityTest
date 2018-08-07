#pragma once

#include "CBaseSystem.hpp"

#include "MyECS.hpp"

class CMovementSystem : public CBaseSystem
{
public:
	CMovementSystem( MyECS &ecs ) :
		m_ecs { ecs }
	{}

	~CMovementSystem()
	{};

	virtual void Run();

private:
	MyECS &m_ecs;
};


#pragma once

#include "CComponentSystem.hpp"

#include "MyECS.hpp"

class CMovementSystem final : public CComponentSystem
{
public:
	CMovementSystem( MyECS &ecs ) :
		m_ecs { ecs }
	{}

	~CMovementSystem()
	{};

	virtual void Process() override;

private:
	MyECS &m_ecs;
};


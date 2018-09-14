#pragma once

#include "CComponentSystem.hpp"

#include "MyECS.hpp"

class CHealthSystem final : public CComponentSystem
{
public:
	CHealthSystem( MyECS &ecs ) :
		m_ecs { ecs }
	{}

	~CHealthSystem()
	{};

	virtual void Process() override;

private:
	MyECS &m_ecs;
};


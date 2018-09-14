#pragma once

#include "CComponentSystem.hpp"

#include "MyECS.hpp"

class CBombSystem final : public CComponentSystem
{
public:
	CBombSystem( MyECS &ecs ) :
		m_ecs { ecs }
	{}

	~CBombSystem()
	{};

	virtual void Process() override;

private:
	MyECS &m_ecs;
};


#pragma once

#include "CComponentSystem.hpp"

#include "MyECS.hpp"

class CBoundingBoxSystem final : public CComponentSystem
{
public:
	CBoundingBoxSystem( MyECS &ecs ) :
		m_ecs { ecs }
	{}

	~CBoundingBoxSystem()
	{};

	virtual void Process() override;

private:
	MyECS &m_ecs;
};


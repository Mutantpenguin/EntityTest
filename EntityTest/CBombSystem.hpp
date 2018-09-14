#pragma once

#include "CComponentSystem.hpp"

#include "CSpatialBase.hpp"

#include "MyECS.hpp"

class CBombSystem final : public CComponentSystem
{
public:
	CBombSystem( MyECS &ecs, const std::shared_ptr< CSpatialBase > &spatial ) :
		m_ecs { ecs },
		m_spatial { spatial }
	{}

	~CBombSystem()
	{};

	virtual void Process() override;

private:
	MyECS &m_ecs;

	const std::shared_ptr< CSpatialBase > m_spatial;
};


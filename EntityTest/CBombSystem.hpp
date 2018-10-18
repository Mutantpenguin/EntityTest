#pragma once

#include "CComponentSystem.hpp"

#include "CBVHBase.hpp"

#include "MyECS.hpp"

class CBombSystem final : public CComponentSystem
{
public:
	CBombSystem( MyECS &ecs, const std::shared_ptr< CBVHBase > &bvh ) :
		m_ecs { ecs },
		m_bvh { bvh }
	{}

	~CBombSystem()
	{};

	virtual void Process() override;

private:
	MyECS &m_ecs;

	const std::shared_ptr< CBVHBase > m_bvh;
};


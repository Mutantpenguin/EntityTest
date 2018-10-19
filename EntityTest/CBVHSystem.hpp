#pragma once

#include <memory>

#include "CComponentSystem.hpp"

#include "MyECS.hpp"

#include "CBVHBase.hpp"

class CBVHSystem final : public CComponentSystem
{
public:
	CBVHSystem( MyECS &ecs, const std::shared_ptr< CBVHBase > &spatial );

	~CBVHSystem()
	{};

	virtual void Process() override;

private:
	MyECS &m_ecs;

	// TODO separate spatial for static and dynamic objects
	const std::shared_ptr< CBVHBase > m_bvh;
};
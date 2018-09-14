#pragma once

#include <memory>

#include "CComponentSystem.hpp"

#include "MyECS.hpp"

#include "CSpatialBase.hpp"

class CSpatialSystem final : public CComponentSystem
{
public:
	CSpatialSystem( MyECS &ecs, const std::shared_ptr< CSpatialBase > &spatial );

	~CSpatialSystem()
	{};

	virtual void Process() override;

private:
	MyECS &m_ecs;

	// TODO separate spatial for static and dynamic objects
	const std::shared_ptr< CSpatialBase > m_spatial;
};

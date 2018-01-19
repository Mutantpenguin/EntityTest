#pragma once

#include "EComponentIndex.hpp"
#include "CBaseComponent.hpp"

class CPhysicsComponent : public CBaseComponent
{
public:
	CPhysicsComponent(const std::shared_ptr< CEntity > parent);
	virtual ~CPhysicsComponent();

	static const std::uint16_t Index = static_cast<std::uint16_t>(EComponentIndex::PHYSICS);
};


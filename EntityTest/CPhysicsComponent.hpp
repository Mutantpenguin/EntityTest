#pragma once
#include "CBaseComponent.hpp"
class CPhysicsComponent : public CBaseComponent
{
public:
	CPhysicsComponent(const std::shared_ptr< CEntity > parent);
	virtual ~CPhysicsComponent();
};


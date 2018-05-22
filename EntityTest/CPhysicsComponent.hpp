#pragma once

#include "CBaseComponent.hpp"

struct CPhysicsComponent final : CBaseComponent< CPhysicsComponent >
{
	CPhysicsComponent()
	{}

	CPhysicsComponent( float p_mass ) :
		mass { p_mass }
	{}

	float mass;
};


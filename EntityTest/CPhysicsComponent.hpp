#pragma once

#include "CBaseComponent.hpp"

struct CPhysicsComponent final : CBaseComponent< CPhysicsComponent >
{
	CPhysicsComponent() noexcept
	{}

	CPhysicsComponent( const float p_mass ) :
		mass { p_mass }
	{}

	float mass = 0.0f;
};


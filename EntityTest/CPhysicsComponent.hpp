#pragma once

#include "Types.hpp"

struct CPhysicsComponent final
{
	CPhysicsComponent() noexcept
	{}

	CPhysicsComponent( const f16 p_mass ) :
		mass { p_mass }
	{}

	f16 mass = 0.0f;
};


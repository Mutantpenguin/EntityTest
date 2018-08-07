#pragma once

struct CPhysicsComponent final
{
	CPhysicsComponent() noexcept
	{}

	CPhysicsComponent( const float p_mass ) :
		mass { p_mass }
	{}

	float mass = 0.0f;
};


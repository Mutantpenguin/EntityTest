#pragma once

struct CPhysicsComponent final
{
	CPhysicsComponent()
	{}

	CPhysicsComponent( float p_mass ) :
		mass { p_mass }
	{}

	float mass;
};


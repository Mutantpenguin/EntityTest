#pragma once

#include <string>

#include "CBaseComponent.hpp"

struct CExplosionComponent final : CBaseComponent< CExplosionComponent >
{
	CExplosionComponent()
	{}

	CExplosionComponent( const float &p_explosionRadius, const float &p_damage ) :
		explosionRadius { p_explosionRadius },
		damage { p_damage }
	{}

	float explosionRadius;
	float damage;
};


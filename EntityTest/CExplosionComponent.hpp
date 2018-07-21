#pragma once

#include <string>

#include "CBaseComponent.hpp"

struct CExplosionComponent final : CBaseComponent< CExplosionComponent >
{
	CExplosionComponent() noexcept
	{}

	CExplosionComponent( const float &p_explosionRadius, const float &p_damage ) :
		explosionRadius { p_explosionRadius },
		damage { p_damage }
	{}

	float explosionRadius = 0.0f;
	float damage = 0.0f;
};


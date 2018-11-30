#pragma once

#include <string>

#include "../Types.hpp"

struct Explosion final
{
	Explosion() noexcept
	{}

	Explosion( const f16 &p_explosionRadius, const f16 &p_damage ) :
		explosionRadius { p_explosionRadius },
		damage { p_damage }
	{}

	f16 explosionRadius = 0.0f;
	f16 damage = 0.0f;
};
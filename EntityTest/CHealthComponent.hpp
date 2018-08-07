#pragma once

#include <cstdint>

struct CHealthComponent final
{
	CHealthComponent() noexcept
	{}

	CHealthComponent( const float p_health ) :
		health { p_health }
	{}

	float health = 0;
};


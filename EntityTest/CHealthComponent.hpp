#pragma once

#include <cstdint>

#include "Types.hpp"

struct CHealthComponent final
{
	CHealthComponent() noexcept
	{}

	CHealthComponent( const f16 p_health ) :
		health { p_health }
	{}

	f16 health = 0;
};


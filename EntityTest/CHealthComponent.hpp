#pragma once

#include <cstdint>

#include "CBaseComponent.hpp"

struct CHealthComponent final : CBaseComponent< CHealthComponent >
{
	CHealthComponent()
	{}

	CHealthComponent( const float p_health ) :
		health { p_health }
	{}

	float health = 0;
};


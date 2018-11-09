#pragma once

#include <string>

#include "Types.hpp"

struct CBombComponent final
{
	CBombComponent() noexcept
	{}

	CBombComponent( const f16 &p_activationRadius ) :
		activationRadius { p_activationRadius }
	{}

	f16 activationRadius = 0.0f;
};


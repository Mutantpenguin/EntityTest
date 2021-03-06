#pragma once

#include "../Types.hpp"

struct Physics final
{
	Physics() noexcept
	{}

	Physics( const f16 p_mass ) :
		mass { p_mass }
	{}

	f16 mass = 0.0f;
};
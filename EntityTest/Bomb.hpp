#pragma once

#include <string>

#include "Types.hpp"

namespace cmpt
{
	struct Bomb final
	{
		Bomb() noexcept
		{}

		Bomb( const f16 &p_activationRadius ) :
			activationRadius { p_activationRadius }
		{}

		f16 activationRadius = 0.0f;
	};
}
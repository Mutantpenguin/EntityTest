#pragma once

#include <cstdint>

#include "Types.hpp"

namespace cmpt
{
	struct Health final
	{
		Health() noexcept
		{}

		Health( const f16 p_health ) :
			health { p_health }
		{}

		f16 health = 0;
	};
}
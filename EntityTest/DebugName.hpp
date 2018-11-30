#pragma once

#include <string>

namespace cmpt
{
	struct DebugName final
	{
		DebugName() noexcept
		{}

		DebugName( const std::string &p_name ) :
			name { p_name }
		{}

		std::string name;
	};
}
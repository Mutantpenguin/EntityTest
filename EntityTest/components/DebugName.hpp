#pragma once

#include <string>

struct DebugName final
{
	DebugName() noexcept
	{}

	DebugName( const std::string &p_name ) :
		name { p_name }
	{}

	std::string name;
};
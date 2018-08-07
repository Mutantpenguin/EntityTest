#pragma once

#include <string>

struct CDebugNameComponent final
{
	CDebugNameComponent() noexcept
	{}

	CDebugNameComponent( const std::string &p_name ) :
		name { p_name }
	{}

	std::string name;
};


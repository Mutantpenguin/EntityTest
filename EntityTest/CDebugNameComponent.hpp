#pragma once

#include <string>

#include "CBaseComponent.hpp"

struct CDebugNameComponent final : CBaseComponent< CDebugNameComponent >
{
	CDebugNameComponent() noexcept
	{}

	CDebugNameComponent( const std::string &p_name ) :
		name { p_name }
	{}

	std::string name;
};


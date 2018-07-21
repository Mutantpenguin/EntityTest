#pragma once

#include <string>

#include "CBaseComponent.hpp"

struct CBombComponent final : CBaseComponent< CBombComponent >
{
	CBombComponent() noexcept
	{}

	CBombComponent( const float &p_activationRadius ) :
		activationRadius { p_activationRadius }
	{}

	float activationRadius = 0.0f;
};


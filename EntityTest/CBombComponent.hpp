#pragma once

#include <string>

#include "CBaseComponent.hpp"

struct CBombComponent final : CBaseComponent< CBombComponent >
{
	CBombComponent()
	{}

	CBombComponent( const float &p_activationRadius ) :
		activationRadius { p_activationRadius }
	{}

	float activationRadius;
};


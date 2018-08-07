#pragma once

#include <string>

struct CBombComponent final
{
	CBombComponent() noexcept
	{}

	CBombComponent( const float &p_activationRadius ) :
		activationRadius { p_activationRadius }
	{}

	float activationRadius = 0.0f;
};


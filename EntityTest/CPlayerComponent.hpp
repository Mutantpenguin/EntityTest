#pragma once

#include <cstdint>

#include "CBaseComponent.hpp"

struct CPlayerComponent final : CBaseComponent< CPlayerComponent >
{
	std::uint8_t Team;
};


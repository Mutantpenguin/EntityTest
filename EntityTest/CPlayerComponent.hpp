#pragma once

#include <cstdint>

#include "CComponent.hpp"

struct CPlayerComponent final : CComponent<CPlayerComponent>
{
	std::uint8_t Team;
};


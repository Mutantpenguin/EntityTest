#pragma once

#include <cstdint>

enum class EComponentIndex : std::uint16_t
{
	CAMERA = 0,
	PLAYER,
	PHYSICS,

	MAX
};


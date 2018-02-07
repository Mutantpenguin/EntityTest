#pragma once

#include <cstdint>

class CPlayerComponent final
{
public:
	CPlayerComponent();
	~CPlayerComponent();

	std::uint8_t Team;
};


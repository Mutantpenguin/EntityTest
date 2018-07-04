#pragma once

#include <cstdint>

#include <glm/glm.hpp>

#include "CBaseComponent.hpp"

struct CMovementComponent final : CBaseComponent< CMovementComponent >
{
public:
	glm::vec3 Direction { 0.0f, 0.0f, 0.0f };
};


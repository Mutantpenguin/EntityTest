#pragma once

#include <cstdint>

#include <glm/glm.hpp>

struct CMovementComponent final
{
public:
	glm::vec3 Direction { 0.0f, 0.0f, 0.0f };
};


#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "CBaseComponent.hpp"

class CTransformComponent final : CBaseComponent< CTransformComponent >
{
public:
	glm::vec3	Position { 0.0f, 0.0f, 0.0f };
	glm::quat	Orientation { 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3	Scale { 1.0f, 1.0f, 1.0f };

	void Rotate( const float pitchAngle, const float yawAngle, const float rollAngle );

	const glm::mat4 ViewMatrix( void ) const;
};
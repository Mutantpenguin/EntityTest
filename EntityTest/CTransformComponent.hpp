#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Types.hpp"

class CTransformComponent final
{
public:
	glm::vec3	Position { 0.0f, 0.0f, 0.0f };
	glm::quat	Orientation { 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3	Scale { 1.0f, 1.0f, 1.0f };

	void Rotate( const f16 pitchAngle, const f16 yawAngle, const f16 rollAngle );

	const glm::mat4 ViewMatrix( void ) const;
};
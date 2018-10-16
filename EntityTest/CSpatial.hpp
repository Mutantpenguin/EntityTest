#pragma once

#include <optional>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "CBoundingBox.hpp"

class CSpatial final
{
public:
	glm::vec3	Position { 0.0f, 0.0f, 0.0f };
	glm::quat	Orientation { 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3	Scale { 1.0f, 1.0f, 1.0f };

	std::optional< glm::vec3 > Size;

	void Rotate( const float pitchAngle, const float yawAngle, const float rollAngle );

	CBoundingBox BoundingBox() const;

	const glm::mat4 ViewMatrix( void ) const;
};
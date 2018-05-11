#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class CTransformComponent final
{
public:
	void Position( const glm::vec3 &position );
	const glm::vec3 &Position( void ) const;

	void Orientation( const glm::quat &orientation );
	const glm::quat &Orientation( void ) const;

	void Scale( const glm::vec3 &position );
	const glm::vec3 &Scale( void ) const;

	void Rotate( const float pitchAngle, const float yawAngle, const float rollAngle );

	const glm::mat4 ViewMatrix( void ) const;

private:
	glm::vec3	m_position { 0.0f, 0.0f, 0.0f };
	glm::quat	m_orientation { 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3	m_scale { 1.0f, 1.0f, 1.0f };
};
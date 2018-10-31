#pragma once

#include <glm/glm.hpp>

class CPlane
{
public:
	CPlane( void ) noexcept;

	CPlane( const glm::vec3 &point, const glm::vec3 &normal );

	void SetNormal( const glm::vec3 &normal );
	const glm::vec3 &Normal( void ) const;

	void SetDistance( float distance );
	float Distance( void ) const;

	void Normalize( void );

	float DistanceToPlane( const glm::vec3 &point ) const;

private:
	glm::vec3	m_normal { 0.0f, 0.0f, 0.0f };
	float		m_distance { 0.0f };
};

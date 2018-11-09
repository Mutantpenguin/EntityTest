#pragma once

#include <glm/glm.hpp>

#include "Types.hpp"

class CPlane
{
public:
	CPlane( void ) noexcept;

	CPlane( const glm::vec3 &point, const glm::vec3 &normal );

	void SetNormal( const glm::vec3 &normal );
	const glm::vec3 &Normal( void ) const;

	void SetDistance( const f16 distance );
	const f16 &Distance( void ) const;

	void Normalize( void );

	f16 DistanceToPlane( const glm::vec3 &point ) const;

private:
	glm::vec3	m_normal { 0.0f, 0.0f, 0.0f };
	f16			m_distance { 0.0f };
};

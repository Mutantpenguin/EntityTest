#pragma once

#include <glm/glm.hpp>

#include "Types.hpp"

class CPlane
{
public:
	CPlane( void ) = delete;

	CPlane( const glm::vec3 &point, const glm::vec3 &normal );
	CPlane( const glm::vec3 &normal, const f16 distance );

	const glm::vec3 &Normal( void ) const;

	const f16 &Distance( void ) const;

private:
	const glm::vec3	m_normal	{ 0.0f, 0.0f, 0.0f };
	const f16		m_distance	{ 0.0f };
};

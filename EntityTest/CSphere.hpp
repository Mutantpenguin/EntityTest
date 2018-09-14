#pragma once

#include <glm/glm.hpp>

class CSphere final
{
public:
	CSphere( const glm::vec3 &position, const float radius ) :
		m_position { position },
		m_radius { radius }
	{};

	const glm::vec3 &Position() const
	{
		return( m_position );
	}

	const float &Radius() const
	{
		return( m_radius );
	}

private:
	const glm::vec3	m_position { 0.0f, 0.0f, 0.0f };
	const float		m_radius { 0.0f };
};

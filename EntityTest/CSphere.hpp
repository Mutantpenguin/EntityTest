#pragma once

#include <glm/glm.hpp>

class CSphere final
{
public:
	CSphere( const glm::vec3 &position, const float radius );

	const glm::vec3 &Position() const;

	const float &Radius() const;

	bool Contains( const glm::vec3 &position ) const;

private:
	const glm::vec3	m_position { 0.0f, 0.0f, 0.0f };
	const float		m_radius { 0.0f };
};

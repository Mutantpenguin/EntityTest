#pragma once

#include <glm/glm.hpp>

class CSphere final
{
public:
	CSphere( const float radius );

	const float &Radius() const;

private:
	const float	m_radius { 0.0f };
};

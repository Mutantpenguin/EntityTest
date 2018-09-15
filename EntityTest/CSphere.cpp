#include "CSphere.hpp"

#include <glm/gtx/norm.hpp>

CSphere::CSphere( const glm::vec3 &position, const float radius ) :
	m_position { position },
	m_radius { radius }
{}

const glm::vec3 &CSphere::Position() const
{
	return( m_position );
}

const float &CSphere::Radius() const
{
	return( m_radius );
}

#include "CSphere.hpp"

#include <glm/gtx/norm.hpp>

CSphere::CSphere( const float radius ) :
	m_radius { radius }
{}

const float &CSphere::Radius() const
{
	return( m_radius );
}

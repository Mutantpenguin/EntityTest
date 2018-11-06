#include "CSphere.hpp"

#include <glm/gtx/norm.hpp>

CSphere::CSphere( const float radius ) :
	m_radius { radius },
	m_radius2 { radius * radius }
{}

const float &CSphere::Radius() const
{
	return( m_radius );
}

const float &CSphere::Radius2() const
{
	return( m_radius2 );
}

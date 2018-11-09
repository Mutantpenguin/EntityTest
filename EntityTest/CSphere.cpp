#include "CSphere.hpp"

#include <glm/gtx/norm.hpp>

CSphere::CSphere( const f16 radius ) :
	m_radius { radius },
	m_radius2 { radius * radius }
{}

const f16 &CSphere::Radius() const
{
	return( m_radius );
}

const f16 &CSphere::Radius2() const
{
	return( m_radius2 );
}

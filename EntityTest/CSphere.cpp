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

bool CSphere::Contains( const glm::vec3 &position ) const
{
	if( glm::length2( m_position - position ) <= std::pow( m_radius, 2 ) )
	{
		return( true );
	}

	return( false );
}

glm::vec3 CSphere::ClosestPoint( const glm::vec3 &position ) const
{
	return( m_position + ( glm::normalize( position - m_position ) * m_radius ) );
}
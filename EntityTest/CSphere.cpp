#include "CSphere.hpp"

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
	if( glm::length( m_position - position ) <= m_radius )
	{
		return( true );
	}

	return( false );
}
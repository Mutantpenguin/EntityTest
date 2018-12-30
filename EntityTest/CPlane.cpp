#include "CPlane.hpp"

CPlane::CPlane( const glm::vec3 &point, const glm::vec3 &normal ) :
	m_normal { normal / glm::length( normal ) },
	m_distance { -glm::dot( normal, point ) / glm::length( normal ) }
{}

CPlane::CPlane( const glm::vec3 &normal, const f16 distance ) :
	m_normal { normal / glm::length( normal ) },
	m_distance { distance / glm::length( normal ) }
{}

const glm::vec3 &CPlane::Normal( void ) const
{
	return( m_normal );
}

const f16 &CPlane::Distance( void ) const
{
	return( m_distance );
}
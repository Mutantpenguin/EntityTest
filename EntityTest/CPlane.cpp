#include "CPlane.hpp"

CPlane::CPlane( void ) noexcept
{}

CPlane::CPlane( const glm::vec3 &point, const glm::vec3 &normal ) :
	m_normal { normal },
	m_distance { -glm::dot( normal, point ) }
{
	Normalize();
}

void CPlane::SetNormal( const glm::vec3 &normal )
{
	m_normal = normal;
}

const glm::vec3 &CPlane::Normal( void ) const
{
	return( m_normal );
}

void CPlane::SetDistance( const f16 distance )
{
	m_distance = distance;
}

const f16 &CPlane::Distance( void ) const
{
	return( m_distance );
}

void CPlane::Normalize( void )
{
	const f16 length = glm::length( m_normal );
	m_normal /= length;
	// TODO is this right? If not we don't need this function and can include it in "SetNormal"
	m_distance /= length;
}

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

void CPlane::SetDistance( float distance )
{
	m_distance = distance;
}

float CPlane::Distance( void ) const
{
	return( m_distance );
}

void CPlane::Normalize( void )
{
	const float length = 1.0f / glm::length( m_normal );
	m_normal *= length;
	m_distance *= length;
}

float CPlane::DistanceToPlane( const glm::vec3 &point ) const
{
	return( glm::dot( m_normal, point ) + m_distance );
}
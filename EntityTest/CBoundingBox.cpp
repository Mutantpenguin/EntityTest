#include "CBoundingBox.hpp"

CBoundingBox::CBoundingBox( const glm::vec3 &min, const glm::vec3 &max ) :
	m_min { min },
	m_max { max }
{}

glm::vec3 CBoundingBox::Center() const
{
	return( ( m_min + m_max ) / 2.0f );
}

glm::vec3 CBoundingBox::Dimensions() const
{
	return( m_max - m_min );
}

void CBoundingBox::MoveTo( const glm::vec3 &position )
{
	auto const movement = position - Center();

	m_min += movement;
	m_max += movement;
}

CBoundingBox::eIntersectionType CBoundingBox::Intersect( const CBoundingBox & boundingBox ) const
{
	if( ( m_max.x < boundingBox.Min().x )
		||
		( m_min.x > boundingBox.Max().x )
		||
		( m_max.y < boundingBox.Min().y )
		||
		( m_min.y > boundingBox.Max().y )
		||
		( m_max.z < boundingBox.Min().z )
		||
		( m_min.z > boundingBox.Max().z ) )
	{
		return( eIntersectionType::OUTSIDE );
	}

	if( ( m_min.x <= boundingBox.Min().x )
		&&
		( m_max.x >= boundingBox.Max().x )
		&&
		( m_min.y <= boundingBox.Min().y )
		&&
		( m_max.y >= boundingBox.Max().y )
		&&
		( m_min.z <= boundingBox.Min().z )
		&&
		( m_max.z >= boundingBox.Max().z ) )
	{
		return( eIntersectionType::INSIDE );
	}

	return( eIntersectionType::INTERSECT );
}

bool CBoundingBox::Contains( const glm::vec3 &position ) const
{
	if( ( m_max.x < position.x )
		||
		( m_min.x > position.x )
		||
		( m_max.y < position.y )
		||
		( m_min.y > position.y )
		||
		( m_max.z < position.z )
		||
		( m_min.z > position.z ) )
	{
		return( false );
	}

	return( true );
}

glm::vec3 CBoundingBox::ClosestPoint( const glm::vec3 &position ) const
{
	glm::vec3 result;

	if( position.x > m_max.x )
	{
		result.x = m_max.x;
	}
	else if( position.x < m_min.x )
	{
		result.x = m_min.x;
	}
	else
	{
		result.x = position.x;
	}

	if( position.y > m_max.y )
	{
		result.y = m_max.y;
	}
	else if( position.y < m_min.y )
	{
		result.y = m_min.y;
	}
	else
	{
		result.y = position.y;
	}

	if( position.z > m_max.z )
	{
		result.z = m_max.z;
	}
	else if( position.z < m_min.z )
	{
		result.z = m_min.z;
	}
	else
	{
		result.z = position.z;
	}

	return( result );
}

const glm::vec3 &CBoundingBox::Min() const
{
	return( m_min );
}

const glm::vec3 &CBoundingBox::Max() const
{
	return( m_max );
}